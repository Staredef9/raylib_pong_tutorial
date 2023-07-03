//following tutorial from Jones but customizing thing a bit 
//codebase is super fixable with more code chunks splittable into non main functions. 
//Raylib is incredibly cool can't wait to create more things with it. 
//https://www.youtube.com/watch?v=LvpS3ILwQNA 

#include "raylib.h"

#define width 800
#define height 600


typedef struct Ball
{
	float ballX;
	float ballY;
	float ballRadius;
	float ballSpeedX;
	float ballSpeedY;
} Ball;

typedef struct Paddle
{
	float x, y;
	float speed;
	float rect_width;
	float rect_height;
	int	  score;

	Rectangle GetRect()
	{
		return Rectangle{ x - rect_width / 2, y - rect_height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangle(x - rect_width/2, y - rect_height / 2, 10, 100, WHITE);
	}
}Paddle;

//TODO: fai init functions sia della palla che dei paddle

int main()
{
	InitWindow(width, height, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.ballX = GetScreenWidth() / 2;
	ball.ballY = GetScreenHeight() / 2;
	ball.ballRadius =  5;
	ball.ballSpeedX = 300;
	ball.ballSpeedY = 300;

	Paddle left_paddle;
	left_paddle.x = 50;
	left_paddle.y = GetScreenHeight() / 2;
	left_paddle.rect_width = 10;
	left_paddle.rect_height = 100;
	left_paddle.speed = 500;
	left_paddle.score = 0;
	
	Paddle right_paddle;
	right_paddle.x = GetScreenWidth() - 50 ;
	right_paddle.y = GetScreenHeight() / 2;
	right_paddle.rect_width = 10;
	right_paddle.rect_height = 100;
	right_paddle.speed = 500;
	right_paddle.score = 0;


	const char* winnerText = nullptr;

	while (!WindowShouldClose())
	{
		ball.ballX += ball.ballSpeedX * GetFrameTime();
		ball.ballY += ball.ballSpeedY * GetFrameTime();

		if (ball.ballY > GetScreenHeight() || ball.ballY < 0)
		{
			ball.ballSpeedY *= -1;
			
		}
		else if (ball.ballX > GetScreenWidth() )
		{
			ball.ballSpeedX *= -1;
			left_paddle.score += 1;
		}
		else if (ball.ballX < 0)
		{
			ball.ballSpeedX *= -1;
			right_paddle.score += 1;
		}

		if (IsKeyDown(KEY_W))
		{
			left_paddle.y -= left_paddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			left_paddle.y += left_paddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			right_paddle.y -= right_paddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			right_paddle.y += right_paddle.speed * GetFrameTime();
		}
		
		if (CheckCollisionCircleRec(Vector2{ ball.ballX, ball.ballY }, ball.ballRadius,left_paddle.GetRect()))
		{
			if (ball.ballSpeedX < 0) {
				ball.ballSpeedX *= -1.1f;
				ball.ballSpeedY = (ball.ballY - left_paddle.y) / (left_paddle.rect_height / 2) * ball.ballSpeedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.ballX, ball.ballY }, ball.ballRadius, right_paddle.GetRect()))
		{
			if (ball.ballSpeedX > 0)
			{
				ball.ballSpeedX *= -1.1f;
				ball.ballSpeedY = (ball.ballY - right_paddle.y) / (right_paddle.rect_height / 2) * ball.ballSpeedX;
			}
		}

		if (right_paddle.score >= 10 && left_paddle.score >= 10)
		{
			winnerText = "Square!";
		} else if (right_paddle.score >= 10)
		{
			winnerText = "Right player wins!";
		} else if (left_paddle.score >= 10)
		{
			winnerText = "Left player wins!";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.ballX = GetScreenWidth() / 2;
			ball.ballY = GetScreenHeight() / 2;
			ball.ballSpeedX = 300;
			ball.ballSpeedY = 300;
			right_paddle.score = 0;
			left_paddle.score = 0;
			winnerText = nullptr;
		}


		//gameloop
		BeginDrawing();
			ClearBackground(BLACK);
			DrawCircle((int)ball.ballX, (int)ball.ballY, (int )ball.ballRadius, RED);
			left_paddle.Draw();
			right_paddle.Draw();
			DrawText(TextFormat("Left Score: %i", left_paddle.score), 150, 50, 20, WHITE);
			DrawText(TextFormat("Right Score: %i", right_paddle.score), 550, 50, 20, WHITE);

			if (winnerText)
			{
				DrawText(winnerText, 200, GetScreenHeight() / 2 - 30, 60, YELLOW);
				right_paddle.x = GetScreenWidth() - 50;
				right_paddle.y = GetScreenHeight() / 2;
				left_paddle.x = 50;
				left_paddle.y = GetScreenHeight() / 2;

			}

			DrawFPS(20, 20);
		EndDrawing();
	}

	CloseWindow();
	return 0;

}