#include"Tutorial.h"
#include"DxLib.h"
#include"Hit.h"
#include"Main.h"
#include"Game.h"
#define PLAYER_MOV_SPEED	6.0f
#define PLAYER_ROT_SPEED	6.0f

void Tutorial::Init()
{
	//	プレイヤーの座標の初期化
	Player_pos.x = WINDOW_W / 2;
	Player_pos.y = WINDOW_H + 50;
	//	大きさの初期化
	//(当たり判定の大きさ)
	Player_size = 5;
	//	プレイヤーの画像の読み込み
	Player_image = LoadGraph("data/Flog.png");

	//	プレイヤーがどこまで進むかを保存する変数
	Player_move.x = WINDOW_W / 2;
	Player_move.y = WINDOW_H + 50;
	//	プレイヤーが何機あるかのカウント
	Player_count = 0;
	//	プレイヤーが同時に動けなくするための変数の初期化
	move_time = 0;
	//	動いていいか判定する変数
	move = true;
	//	プレイヤーのゴール判定
	goal = false;

	//	一度使ったゴールは使えなくするための変数
	for (int i = 0; i <= 4; i++)
	{
		goal_dead_count[i] = 0;
		//	ゴールした際にゴールの色を変える
		goal_juge_color[i] = 255;
	}

	//	ゴールカウントの初期化
	goal_count = 0;

	goal_count_check = 5;

	//	プレイヤーが敵にぶつかったときの処理
	dead = false;

	wood_out = false;

	//	川に入ったときの変数の初期化
	river_in = false;
	Player_flow = -5.0f;

	//	制限時間の変数の初期化
	time = 1800;
	time_start = false;


		for (int i = 0; i <= 8; i++)
	{
		//	右から出てくるよう
		Enemy_pos_Right[i].x = WINDOW_W;
		Enemy_pos_Right[i].y = WINDOW_W / 2;
		//	左から出てくるよう
		Enemy_pos_Left[i].x = WINDOW_W;
		Enemy_pos_Left[i].y = WINDOW_W / 2;

	}

	//	Enemyの画像
	Car_red = LoadGraph("data/car_red.png");
	Car_green = LoadGraph("data/car_green.png");
	Car_blue = LoadGraph("data/car_skyblue.png");
	Car_black = LoadGraph("data/car_black.png");
	//	逆向き
	Car_red_gyaku = LoadGraph("data/car_red_gyaku.png");
	Car_green_gyaku = LoadGraph("data/car_green_gyaku.png");
	Car_blue_gyaku = LoadGraph("data/car_skyblue_gyaku.png");
	Car_black_gyaku = LoadGraph("data/car_black_gyaku.png");


	//	Enemyの大きさの初期化
	Enemy_size = 10;

	//	重なってる敵をずらす処理
	//	右から出てくる敵
	Enemy_pos_Right[1].x =+200;
	Enemy_pos_Right[4].x = +200;
	Enemy_pos_Right[7].x = +250;

	Enemy_pos_Right[2].x = +400;
	Enemy_pos_Right[5].x = +400;
	Enemy_pos_Right[8].x = +450;

	//	左から出てくる敵
	Enemy_pos_Left[1].x = +200;
	Enemy_pos_Left[4].x = +200;
	Enemy_pos_Left[7].x = +250;

	Enemy_pos_Left[2].x = +400;
	Enemy_pos_Left[5].x = +400;
	Enemy_pos_Left[8].x = +450;

	//	X座標をずらすための処理　これがないと車が二列で走っているように見えるので
	Enemy_pos_Left[0].x += 50;
	Enemy_pos_Left[1].x += 50;
	Enemy_pos_Left[2].x += 50;

	//	川の座標の変数を初期化
	//	右流れの川
	Enemy_pos_River_Right[0].x = 900;
	Enemy_pos_River_Right[1].x = 0;

	//	左流れの初期化
	Enemy_pos_River_Left[0].x = 900;
	Enemy_pos_River_Left[1].x = 100;
	//	右流れの川
	Enemy_pos_River_Right[2].x = 1400;
	Enemy_pos_River_Right[3].x = 500;


}
void Tutorial::Update()
{
	goal_count_check = 5 - goal_count;

	if (time_start) {
		time--;
	}
	move_time++;
	//	連打で動けないようにカウントをとる
	if (move_time >= 10)
	{
		move = true;
	}

	if (move)
	{
		//	プレイヤー操作処理
		if (PushHitKey(KEY_INPUT_LEFT))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_RIGHT))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_UP))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_DOWN))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		//	プレイヤー操作処理 WASDキー用
		if (PushHitKey(KEY_INPUT_A))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_D))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_W))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_S))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}

		//	画面外に行かないようにする処理
		if (Player_move.x >= WINDOW_W - 50)
		{
			Player_move.x = WINDOW_H - 50;

		}
		if (Player_move.x <= 50)
		{
			Player_move.x = 50;
		}
		if (Player_move.y >= WINDOW_H - 25)
		{
			Player_move.y = WINDOW_H - 25;
		}
	}
	if (Player_move.x >= Player_pos.x)
	{
		Player_pos.x += 5;
	}
	if (Player_move.y <= Player_pos.y)
	{
		Player_pos.y -= 5;
	}
	if (Player_move.x <= Player_pos.x)
	{
		Player_pos.x -= 5;
	}
	if (Player_move.y >= Player_pos.y)
	{
		Player_pos.y += 5;
	}


	//	川に入ったときの処理

	/*if (Player_pos.y <= 100)
	{
		Player_pos.y = 50;
	}*/

	//	ゴールした時の処理
	if (Player_pos.y <= 50)
	{

		if (Player_pos.x >= WINDOW_W / 2 + 300 && Player_pos.x <= WINDOW_W / 2 + 375)
		{

			//	一度ゴールしたら使えなくする
			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;
			goal_dead_count[0]++;
			goal_juge_color[0] = 0;

		}

		else if (Player_pos.x >= WINDOW_W / 2 + 50 && Player_pos.x <= WINDOW_W / 2 + 125)
		{
			//	一度ゴールしたら使えなくする

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_W + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[1]++;
			goal_juge_color[1] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 2 - 175 && Player_pos.x <= WINDOW_W / 2 - 100)
		{
			//	一度ゴールしたら使えなくする

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[2]++;
			goal_juge_color[2] = 0;
		}


		else if (Player_pos.x >= WINDOW_W / 4 && Player_pos.x <= WINDOW_W / 4 + 75)
		{
			//	一度ゴールしたら使えなくする

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[3]++;
			goal_juge_color[3] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 10 && Player_pos.x <= WINDOW_W / 10 + 75)
		{

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[4]++;
			goal_juge_color[4] = 0;
		}




		else
		{
			dead = true;
		}

	}

	//	時間切れでゲームオーバー　
	if (time <= -1)
	{
		dead = true;
	}
	if (goal_dead_count[0] >= 2)
	{
		dead = true;

	}

	if (goal_dead_count[1] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[2] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[3] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[4] >= 2)
	{
		dead = true;

	}

	if (goal_count >= 5)
	{
		goal = true;
	}

}
void Tutorial::Draw()
{

}
void Tutorial::Exit()
{

}