#include"Tutorial.h"
#include"DxLib.h"
#include"Hit.h"
#include"Main.h"
#include"Game.h"
#define PLAYER_MOV_SPEED	6.0f
#define PLAYER_ROT_SPEED	6.0f

void Tutorial::Init()
{
	//	�v���C���[�̍��W�̏�����
	Player_pos.x = WINDOW_W / 2;
	Player_pos.y = WINDOW_H + 50;
	//	�傫���̏�����
	//(�����蔻��̑傫��)
	Player_size = 5;
	//	�v���C���[�̉摜�̓ǂݍ���
	Player_image = LoadGraph("data/Flog.png");

	//	�v���C���[���ǂ��܂Ői�ނ���ۑ�����ϐ�
	Player_move.x = WINDOW_W / 2;
	Player_move.y = WINDOW_H + 50;
	//	�v���C���[�����@���邩�̃J�E���g
	Player_count = 0;
	//	�v���C���[�������ɓ����Ȃ����邽�߂̕ϐ��̏�����
	move_time = 0;
	//	�����Ă��������肷��ϐ�
	move = true;
	//	�v���C���[�̃S�[������
	goal = false;

	//	��x�g�����S�[���͎g���Ȃ����邽�߂̕ϐ�
	for (int i = 0; i <= 4; i++)
	{
		goal_dead_count[i] = 0;
		//	�S�[�������ۂɃS�[���̐F��ς���
		goal_juge_color[i] = 255;
	}

	//	�S�[���J�E���g�̏�����
	goal_count = 0;

	goal_count_check = 5;

	//	�v���C���[���G�ɂԂ������Ƃ��̏���
	dead = false;

	wood_out = false;

	//	��ɓ������Ƃ��̕ϐ��̏�����
	river_in = false;
	Player_flow = -5.0f;

	//	�������Ԃ̕ϐ��̏�����
	time = 1800;
	time_start = false;


		for (int i = 0; i <= 8; i++)
	{
		//	�E����o�Ă���悤
		Enemy_pos_Right[i].x = WINDOW_W;
		Enemy_pos_Right[i].y = WINDOW_W / 2;
		//	������o�Ă���悤
		Enemy_pos_Left[i].x = WINDOW_W;
		Enemy_pos_Left[i].y = WINDOW_W / 2;

	}

	//	Enemy�̉摜
	Car_red = LoadGraph("data/car_red.png");
	Car_green = LoadGraph("data/car_green.png");
	Car_blue = LoadGraph("data/car_skyblue.png");
	Car_black = LoadGraph("data/car_black.png");
	//	�t����
	Car_red_gyaku = LoadGraph("data/car_red_gyaku.png");
	Car_green_gyaku = LoadGraph("data/car_green_gyaku.png");
	Car_blue_gyaku = LoadGraph("data/car_skyblue_gyaku.png");
	Car_black_gyaku = LoadGraph("data/car_black_gyaku.png");


	//	Enemy�̑傫���̏�����
	Enemy_size = 10;

	//	�d�Ȃ��Ă�G�����炷����
	//	�E����o�Ă���G
	Enemy_pos_Right[1].x =+200;
	Enemy_pos_Right[4].x = +200;
	Enemy_pos_Right[7].x = +250;

	Enemy_pos_Right[2].x = +400;
	Enemy_pos_Right[5].x = +400;
	Enemy_pos_Right[8].x = +450;

	//	������o�Ă���G
	Enemy_pos_Left[1].x = +200;
	Enemy_pos_Left[4].x = +200;
	Enemy_pos_Left[7].x = +250;

	Enemy_pos_Left[2].x = +400;
	Enemy_pos_Left[5].x = +400;
	Enemy_pos_Left[8].x = +450;

	//	X���W�����炷���߂̏����@���ꂪ�Ȃ��ƎԂ����ő����Ă���悤�Ɍ�����̂�
	Enemy_pos_Left[0].x += 50;
	Enemy_pos_Left[1].x += 50;
	Enemy_pos_Left[2].x += 50;

	//	��̍��W�̕ϐ���������
	//	�E����̐�
	Enemy_pos_River_Right[0].x = 900;
	Enemy_pos_River_Right[1].x = 0;

	//	������̏�����
	Enemy_pos_River_Left[0].x = 900;
	Enemy_pos_River_Left[1].x = 100;
	//	�E����̐�
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
	//	�A�łœ����Ȃ��悤�ɃJ�E���g���Ƃ�
	if (move_time >= 10)
	{
		move = true;
	}

	if (move)
	{
		//	�v���C���[���쏈��
		if (PushHitKey(KEY_INPUT_LEFT))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_RIGHT))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_UP))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_DOWN))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		//	�v���C���[���쏈�� WASD�L�[�p
		if (PushHitKey(KEY_INPUT_A))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_D))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_W))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_S))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	�����o�����琧�����Ԃ������o��
			time_start = true;
		}

		//	��ʊO�ɍs���Ȃ��悤�ɂ��鏈��
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


	//	��ɓ������Ƃ��̏���

	/*if (Player_pos.y <= 100)
	{
		Player_pos.y = 50;
	}*/

	//	�S�[���������̏���
	if (Player_pos.y <= 50)
	{

		if (Player_pos.x >= WINDOW_W / 2 + 300 && Player_pos.x <= WINDOW_W / 2 + 375)
		{

			//	��x�S�[��������g���Ȃ�����
			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;
			goal_dead_count[0]++;
			goal_juge_color[0] = 0;

		}

		else if (Player_pos.x >= WINDOW_W / 2 + 50 && Player_pos.x <= WINDOW_W / 2 + 125)
		{
			//	��x�S�[��������g���Ȃ�����

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_W + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[1]++;
			goal_juge_color[1] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 2 - 175 && Player_pos.x <= WINDOW_W / 2 - 100)
		{
			//	��x�S�[��������g���Ȃ�����

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[2]++;
			goal_juge_color[2] = 0;
		}


		else if (Player_pos.x >= WINDOW_W / 4 && Player_pos.x <= WINDOW_W / 4 + 75)
		{
			//	��x�S�[��������g���Ȃ�����

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[3]++;
			goal_juge_color[3] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 10 && Player_pos.x <= WINDOW_W / 10 + 75)
		{

			goal_count++;
			//	�v���C���[�������ʒu�ɖ߂�
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	�S�[�������琧�����Ԃ�������
			time = 1800;
			//	�S�[�������琧�����Ԃ��~�߂�
			time_start = false;

			goal_dead_count[4]++;
			goal_juge_color[4] = 0;
		}




		else
		{
			dead = true;
		}

	}

	//	���Ԑ؂�ŃQ�[���I�[�o�[�@
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