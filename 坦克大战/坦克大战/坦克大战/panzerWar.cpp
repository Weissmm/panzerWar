#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#pragma comment (lib, "Winmm.lib") //����������
/*
#define UP 0
#define DOWN  1
#define LEFT 2
#define RIGHT 3
*/

#define SUCCESS 0
#define FAILURE 1

#define ENEMY_NUM 10

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


//̹�˽ṹ��
struct tank_s {
	int x;  //̹���ڵ�ͼ������������
	int y;  //̹���ڵ�ͼ���������ڵ���
	DIRECTION direction;  //̹�˵ķ����ϡ��¡�����
	int live;       //�Ƿ����� 1-����  0-����
};

//�ӵ��ṹ��
struct bullet_s {
	int pos_x;   //�ӵ��ڡ�Ϸ̨���ϵĺ�����
	int pos_y;   //�ӵ��ڡ�Ϸ̨���ϵ�������
	DIRECTION  direction; //�ӵ�����
	int status;  //�ӵ��Ƿ����
};


//�����ͼ����
int map[26][26] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 2, 2, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 2, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


void menu();
void init_map();
void init_map_2(int* map, int rows, int cols);
int play();
int do_tank_walk(tank_s* tank, DIRECTION direction, IMAGE* img, int step);
void set_prop_map(int x, int y, int val);
int bullet_action(bullet_s* bullet, tank_s* enemy_tank);
void tank_walk(tank_s* tank, DIRECTION direction, IMAGE* img);
DIRECTION  enemy_direction(tank_s* tank, int x, int y);
void game_over(int result);

int main(void) {
	int result = SUCCESS;
	//���̨
	initgraph(650, 650);
	//AGAIN:
		//��ʼ��������ʾ�˵�
	menu();

	//��ʼ����ͼ
	//init_map_2(&map[0][0], 26, 26);
	init_map();

	//�ж�play �Ľ��������1˵���ҷ�ʧ�ܣ������ҷ�ʤ��
	result = play();

	//��ʾ��Ϸ���
	game_over(result);

	system("pause");
	closegraph();
	exit(0);
}

void game_over(int result) {
	IMAGE img;
	if (result == SUCCESS) {
		loadimage(&img, _T("success.jpg"), 500, 250);//_T()֧��Unicode
		putimage(80, 200, &img);

	}
	else {
		loadimage(&img, _T("failure.jpg"), 500, 250);
		putimage(80, 200, &img);
	}
	_getch();
}

void menu() {
	//��ʾ logo
	IMAGE logo_img;
	loadimage(&logo_img, _T("logo.bmp"), 433, 147);
	putimage(110, 20, &logo_img);

	//ʵ�ֵ�����ť
	setlinecolor(WHITE);
	setfillcolor(BLACK);

	fillrectangle(230, 200, 310, 240);
	settextstyle(25, 0, _T("����"));
	outtextxy(240, 210, _T("˵ ��"));

	fillrectangle(350, 200, 430, 240);
	outtextxy(360, 210, _T("�� ʼ"));

	MOUSEMSG mouse;
	IMAGE illustrate_img;
	loadimage(&illustrate_img, _T("illustrate.jpg"), 300, 300);



	while (1 == 1) {			//�ж����λ��
		mouse = GetMouseMsg();

		switch (mouse.uMsg) {
		case WM_MOUSEMOVE:
			if ((mouse.x > 230 && mouse.x < 310) && (mouse.y > 200 && mouse.y < 240)) {
				putimage(150, 250, &illustrate_img);
			}
			else {
				solidrectangle(150, 250, 450, 550);
			}
			break;
		case WM_LBUTTONDOWN:
			if ((mouse.x > 350 && mouse.x < 430) && (mouse.y > 200 && mouse.y < 240)) {
				cleardevice();
				return;
			}
		}
	}
}

/*
��ʼ����ͼ��������ǽΪ1����������ǽΪ 2����ӥ (3 ,4)
*/
void init_map() {
	int i, j;
	IMAGE img_home, img_wall_1, img_wall_2;

	loadimage(&img_home, _T("home.jpg"), 50, 50);// ��ӥ
	loadimage(&img_wall_1, _T("wall1.jpg"), 25, 25);//����������ǽ
	loadimage(&img_wall_2, _T("wall2.jpg"), 25, 25);//��������ǽ

	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (map[i][j] == 1) {
				putimage(25 * j, 25 * i, &img_wall_2);
			}
			else if (map[i][j] == 2) {
				putimage(25 * j, 25 * i, &img_wall_1);
			}
			else if (map[i][j] == 3) {
				putimage(25 * j, 25 * i, &img_home);
				set_prop_map(j, i, 4);

			}
		}
	}
}


void set_prop_map(int x, int y, int val) {
	map[y][x] = val;
	map[y][x + 1] = val;
	map[y + 1][x] = val;
	map[y + 1][x + 1] = val;
}

/*
*����̹�˰���Ӧ�ķ���ǰ��һ��
*����ֵ��ʧ�� - 0   �ɹ� 1
*/
int do_tank_walk(tank_s* tank, DIRECTION direction, IMAGE* img, int step) {
	int new_x = tank->x;
	int new_y = tank->y;

	int old_prop = map[tank->y][tank->x];

	if (step == 1) {//̹��ǰ��һ��
		if (direction == UP) {
			new_y -= 1;
		}
		else if (direction == DOWN) {
			new_y += 1;
		}
		else if (direction == LEFT) {
			new_x -= 1;
		}
		else if (direction == RIGHT) {
			new_x += 1;
		}
		else {
			return 0; //��Ч�ķ���
		}

		set_prop_map(tank->x, tank->y, 0);
	}

	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);

	if (step == 1) {
		set_prop_map(new_x, new_y, old_prop);
		tank->x = new_x;
		tank->y = new_y;
	}
	putimage(tank->x * 25, tank->y * 25, img);
	return 1;
}


/*
 * ʵ���ӵ����к���ײ��⣬��������Ϸ���
 * ���أ�1 -��ʾ��Ϸʧ��  0 - ������Ϸ
*/
int bullet_action(bullet_s* bullet, tank_s* enemy_tank) {
	int x, y, x1, y1;  //�ӵ�Ŀǰ���ڵĶ�ά�����е�����

	x = bullet->pos_x / 25;
	y = bullet->pos_y / 25;

	//1.������һ�λ��Ƶ��ӵ�
	setfillcolor(BLACK);
	solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x + 3, bullet->pos_y + 3);

	//2.���ݷ�������ӵ��ڡ�Ϸ̨���ϵ�����
	if (bullet->direction == UP) {
		bullet->pos_y -= 2;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == DOWN) {
		bullet->pos_y += 2;
		x1 = x + 1;
		y1 = y;
	}
	else if (bullet->direction == LEFT) {
		bullet->pos_x -= 2;
		x1 = x;
		y1 = y + 1;

	}
	else if (bullet->direction == RIGHT) {
		bullet->pos_x += 2;
		x1 = x;
		y1 = y + 1;
	}
	else {
		return 0;
	}

	if (bullet->pos_x < 0 || bullet->pos_x>650 || bullet->pos_y < 0 || bullet->pos_y>650) {
		bullet->status = 0;
		return 0;
	}

	//��ײ���
	if (map[y][x] == 4 || map[y1][x1] == 4) {//������ӥ
		return 1;
	}

	if (map[y][x] == 200 || map[y1][x1] == 200) {//�����ҷ�̹��
		return 1;
	}

	if ((map[y][x] >= 100 && map[y][x] <= 109) || (map[y1][x1] >= 100 && map[y1][x1] <= 109)) {
		tank_s* tank = NULL;
		bullet->status = 0;

		if (map[y][x] >= 100 && map[y][x] <= 109) {
			tank = enemy_tank + (map[y][x] - 100);
		}
		else tank = enemy_tank + (map[y1][x1] - 100);

		tank->live = 0;
		set_prop_map(tank->x, tank->y, 0);
		setfillcolor(BLACK);
		solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);

	}



	if (map[y][x] == 1) {//�ӵ����п�������ǽ
		map[y][x] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x * 25, y * 25, x * 25 + 25, y * 25 + 25);
	}
	else if (map[y][x] == 2) {
		bullet->status = 0;
	}

	if (map[y1][x1] == 1) {//�ӵ����п�������ǽ
		map[y1][x1] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25, y1 * 25 + 25);
	}
	else if (map[y1][x1] == 2) {
		bullet->status = 0;
	}


	//3.���»����ӵ�
	if (bullet->status == 1) {
		setfillcolor(WHITE);
		solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x + 3, bullet->pos_y + 3);
	}
	return 0;
}


void tank_walk(tank_s* tank, DIRECTION direction, IMAGE* img) {
	switch (direction) {
	case LEFT:  //��
		if (tank->direction == LEFT && (tank->x - 1) >= 0 && map[tank->y][tank->x - 1] == 0 && map[tank->y + 1][tank->x - 1] == 0) {//����ǿյ�
			do_tank_walk(tank, LEFT, img, 1);
		}
		else if (tank->direction != LEFT) {
			tank->direction = LEFT;
			do_tank_walk(tank, LEFT, img, 0);
		}
		break;
	case UP:  //��
		if (tank->direction == UP && (tank->y - 1) >= 0 && map[tank->y - 1][tank->x] == 0 && map[tank->y - 1][tank->x + 1] == 0) {//�ϱ��ǿյ�
			do_tank_walk(tank, UP, img, 1);
		}
		else if (tank->direction != UP) {
			tank->direction = UP;
			do_tank_walk(tank, UP, img, 0);
		}
		break;
	case DOWN:  //��
		if (tank->direction == DOWN && (tank->y + 2) <= 25 && map[tank->y + 2][tank->x] == 0 && map[tank->y + 2][tank->x + 1] == 0) {//�±��ǿյ�
			do_tank_walk(tank, DOWN, img, 1);
		}
		else if (tank->direction != DOWN) {
			tank->direction = DOWN;
			do_tank_walk(tank, DOWN, img, 0);
		}
		break;
	case RIGHT:  //��
		if (tank->direction == RIGHT && (tank->x + 2) <= 25 && map[tank->y][tank->x + 2] == 0 && map[tank->y + 1][tank->x + 2] == 0) {//�ұ��ǿյ�
			do_tank_walk(tank, RIGHT, img, 1);
		}
		else if (tank->direction != RIGHT) {
			tank->direction = RIGHT;
			do_tank_walk(tank, RIGHT, img, 0);
		}
		break;
	}

}

/*
*����Ŀ��λ�ã������з�̹�˵ķ���
*
*/

DIRECTION  enemy_direction(tank_s* tank, int x, int y) {
	int r = rand() % 100;

	if (tank->x > x) { //Ŀ�������
		if (tank->y > y) {//Ŀ�������Ϸ�
			if (r <= 50) return UP;
			else return LEFT;
		}
		else {         //Ŀ�������·�
			if (r <= 50) return DOWN;
			else return LEFT;
		}

	}
	else {//Ŀ�����ұ�
		if (tank->y > y) {//Ŀ�������Ϸ�
			if (r <= 50) return UP;
			else return RIGHT;
		}
		else {         //Ŀ�������·�
			if (r <= 50) return DOWN;
			else return RIGHT;
		}

	}

}

void tank_fire(tank_s* tank, bullet_s* bullet, int need_sound) {
	if (bullet->status == 0) {
		if (need_sound) PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (tank->direction == UP) {
			bullet->pos_x = tank->x * 25 + 23;
			bullet->pos_y = tank->y * 25 - 3;
		}
		else if (tank->direction == LEFT) {
			bullet->pos_x = tank->x * 25 - 3;
			bullet->pos_y = tank->y * 25 + 23;
		}
		else if (tank->direction == DOWN) {
			bullet->pos_x = tank->x * 25 + 23;
			bullet->pos_y = tank->y * 25 + 50;
		}
		else if (tank->direction == RIGHT) {
			bullet->pos_x = tank->x * 25 + 50;
			bullet->pos_y = tank->y * 25 + 23;
		}

		bullet->direction = tank->direction;
		bullet->status = 1;
	}

}

/*****************************
*ʵ����Ϸ����
******************************/
int play() {

	tank_s my_tank;  //�ҷ�̹��
	bullet_s my_bullet;//�ҷ�̹�˷�����ӵ�

	tank_s enemy_tank[ENEMY_NUM]; //�з�̹��
	bullet_s enemy_bullet[ENEMY_NUM];//�з�̹�˷�����ӵ�

	IMAGE my_tank_img[4];
	IMAGE enemy_tank_img[4];
	int key;
	int times = 1;//��¼��ǰ��������ߴ�����û��10ms
	int enemy_total = 0;

	//��ʼ�����������
	srand(time(NULL));

	//�����ҷ�̹�˵�ͼƬ
	loadimage(&my_tank_img[UP], _T("tank_up.jpg"), 50, 50);
	loadimage(&my_tank_img[DOWN], _T("tank_down.jpg"), 50, 50);
	loadimage(&my_tank_img[LEFT], _T("tank_left.jpg"), 50, 50);
	loadimage(&my_tank_img[RIGHT], _T("tank_right.jpg"), 50, 50);

	//���صз�̹�˵�ͼƬ
	loadimage(&enemy_tank_img[UP], _T("enemy_tank_up.jpg"), 50, 50);
	loadimage(&enemy_tank_img[DOWN], _T("enemy_tank_down.jpg"), 50, 50);
	loadimage(&enemy_tank_img[LEFT], _T("enemy_tank_left.jpg"), 50, 50);
	loadimage(&enemy_tank_img[RIGHT], _T("enemy_tank_right.jpg"), 50, 50);

	my_bullet.status = 0; //�ӵ�Ŀǰ�в�����

	//�趨�ҷ�̹�˵ĳ�����λ��
	my_tank.x = 8;
	my_tank.y = 24;
	my_tank.live = 1;
	my_tank.direction = UP;
	set_prop_map(my_tank.x, my_tank.y, 200);

	//���õз�̹�˳�����λ��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (i % 3 == 0) {
			enemy_tank[i].x = 0;
		}
		else if (i % 3 == 1) {
			enemy_tank[i].x = 12;
		}
		else if (i % 3 == 2) {
			enemy_tank[i].x = 24;
		}
		enemy_tank[i].direction = DOWN;
		enemy_tank[i].y = 0;
		enemy_tank[i].live = 1;
		//set_prop_map(enemy_tank[i].x, enemy_tank[i].y, 100+i);
		enemy_bullet[i].status = 0;

	}
	//����������
	mciSendString(_T("open background.wav alias a1 wait"), NULL, 0, NULL);
	mciSendString(_T("play a1"), 0, 0, 0);

	//ǰ3��̹�������ǳ�
	do_tank_walk(&enemy_tank[0], DOWN, &enemy_tank_img[DOWN], 0);
	set_prop_map(enemy_tank[0].x, enemy_tank[0].y, 100);
	do_tank_walk(&enemy_tank[1], DOWN, &enemy_tank_img[DOWN], 0);
	set_prop_map(enemy_tank[1].x, enemy_tank[1].y, 101);
	do_tank_walk(&enemy_tank[2], DOWN, &enemy_tank_img[DOWN], 0);
	set_prop_map(enemy_tank[2].x, enemy_tank[2].y, 102);
	enemy_total = 3;

	putimage(my_tank.x * 25, my_tank.y * 25, &my_tank_img[my_tank.direction]);

	while (1) {
		if (times > 0 && times % 1000 == 0 && enemy_total < ENEMY_NUM) {
			//�жϳ����Ķ�ά�����λ���Ƿ��Ѿ���̹�˴��ڣ�����ʵ��
			set_prop_map(enemy_tank[enemy_total].x, enemy_tank[enemy_total].y, 100 + enemy_total);
			enemy_total++;
		}
		if (times % 200 == 0) {//2ms �����з�̹�˵ķ���
			for (int i = 0; i < enemy_total; i++) {
				if (enemy_tank[i].live == 0) continue;
				if (i % 2 == 0) {//�����ҷ��ϳ�
					DIRECTION d = enemy_direction(&enemy_tank[i], 12, 24);
					tank_walk(&enemy_tank[i], d, &enemy_tank_img[d]);
				}
				else {//�����ҷ�̹��
					DIRECTION d = enemy_direction(&enemy_tank[i], my_tank.x, my_tank.y);
					tank_walk(&enemy_tank[i], d, &enemy_tank_img[d]);
				}

				tank_fire(&enemy_tank[i], &enemy_bullet[i], 0);
			}
		}
		else if (times % 50 == 0) {//0.5ms�ƶ��з��������̹��
			for (int i = 0; i < enemy_total; i++) {
				if (enemy_tank[i].live) {
					tank_walk(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
				}
			}

		}

		if (_kbhit()) {
			key = _getch();

			switch (key) {
			case 'a':  //��
				tank_walk(&my_tank, LEFT, &my_tank_img[LEFT]);
				break;
			case 'w':  //��
				tank_walk(&my_tank, UP, &my_tank_img[UP]);
				break;
			case 's':  //��
				tank_walk(&my_tank, DOWN, &my_tank_img[DOWN]);
				break;
			case 'd':  //��
				tank_walk(&my_tank, RIGHT, &my_tank_img[RIGHT]);
				break;
			case 'j':  //����
				tank_fire(&my_tank, &my_bullet, 1);
				break;
			case 'p':  //��ͣ
				system("pause");
				break;
			default:   //���������������봦��
				break;
			}
		}
		if (my_bullet.status == 1) {
			if (bullet_action(&my_bullet, enemy_tank)) return FAILURE;//�ҷ��ӵ��˶�Ч��
		}
		for (int i = 0; i < ENEMY_NUM; i++) {//�з��ӵ��˶�Ч��
			if (enemy_bullet[i].status == 1) {
				if (bullet_action(&enemy_bullet[i], enemy_tank)) return FAILURE;
			}
		}
		//�жϵз�̹���Ƿ�ȫ��������
		int isWin = 1;
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (enemy_tank[i].live == 1) isWin = 0;
		}

		if (isWin) return SUCCESS;

		Sleep(10);
		times++;
	}
}
