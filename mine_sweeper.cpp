// mine_sweeper.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sizeH 10
#define sizeW 10

//マップの初期化関数
void Reset_map(char map[sizeH][sizeW]) {
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			map[i][j] = '?';
		}
	}
}

//マップの出力関数
void Output_map(char map[sizeH][sizeW]) {
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (int i = 0; i < sizeH; i++) {
		printf("%d", i);

		for (int j = 0; j < sizeW; j++) {
			printf(" %c", map[i][j]);
		}
		putchar('\n');
	}
}

//入力の検査関数
int Check_input(char c) {
	//charからintに変換
	int input = (int)c - 48;
	//printf("input = %d\n", input);

	if (input >= 0 && input < sizeH) {
		return 1; //OK
	}
	else {
		return 0; //NG
	}
}

//入力バッファのクリア関数
void Delete_input(void) {
	char input = 0;

	//不要な入力の除去
	while (input != '\n') {
		input = getchar();
	}
}

//入力の取得関数
int Input_line() {
	while (1) {
		char input = 0;
		int inputFlag = 0; //入力の判定用

		printf("\n入力(縦座標)：");
		scanf_s("%c", &input, 1);

		//入力の検査
		inputFlag = Check_input(input);

		//次の処理に進む
		if (inputFlag == 1) {
			Delete_input();

			return (int)input - 48;
		}

		//入力に戻る
		else {
			printf("\n入力が正しくない\n");
			Delete_input();

			continue;
		}
	}
}

void Game_manager(char map[sizeH][sizeW]) {

	while (1) {
		//マップの初期化と表示
		Reset_map(map);
		Output_map(map);

		//入力の取得
		int coordX = 0;
		int coordY = 0;
		coordX = Input_line();
		printf("\ncoordX = %d\n", coordX);
		coordY = Input_line();
		printf("\ncoordY = %d\n", coordY);


	}
}

int main()
{
	char map[sizeH][sizeW];
	
	Game_manager(map);

	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
