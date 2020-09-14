#include "DxLib.h"

#define GAME_WIDTH		640	//��ʂ̉��̑傫��
#define GAME_HEIGHT		480	//��ʂ̏c�̑傫��
#define GAME_COLOR		32	//��ʂ̃J���[�s�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"Dxlib_Movie"	//�E�B���h�E�̃^�C�g��

//MOVIE�t�H���_�ƁAmp4�t�@�C�����ǉ����Ă�������
#define MOVIE_PATH  ".\\MOVIE\\srn.mp4"	//����p�X

//����̃n���h��
int handle = -1;

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txt���o�͂��Ȃ�
	//log.txt�͈����o�͂��邩�炢��Ȃ������H
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�̓E�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	//DXLib����������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//����̓ǂݍ���
	handle = LoadGraph(MOVIE_PATH);

	//�������[�v
	while (TRUE)
	{
		//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ProcessMessage() != 0)
		{
			break;
		}

		//��ʂ������ł��Ȃ������Ƃ��A�����I��
		if (ClearDrawScreen() != 0)
		{
			break;
		}

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0);	//����̍Đ��o�[���ŏ��ɂ���
			PlayMovieToGraph(handle);		//������Đ���Ԃɂ���

			//����̉��𒲐�����(0�������`255������̉���)
			ChangeMovieVolumeToGraph(127, handle);
		}

		//�^�C�g������`��
		//DrawGraph(0, 0, handle, FALSE);

		//����T�C�Y�𓯂��ɂ���(�����x������)
		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE);

		DrawString(0, 0, "������Đ����Ă��܂��E�E�E", GetColor(255, 255, 255));
		DrawString(0, 20, "�\�A���Ƃ̓���", GetColor(255, 255, 255));

		//���j�^�̃��t���b�V����0�Ƃ̑����ŗ���ʂ��ĕ`��
		ScreenFlip();
	}

	//DX���C�u�����g�p�̏I������
	DxLib_End();

	//����̍폜
	DeleteGraph(handle);

	return 0;
}
