// mine_sweeper.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sizeH 10
#define sizeW 10
#define bomb 15

//マップの初期化関数
void Reset_map(char map[sizeH][sizeW]) {
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			map[i][j] = '?';
		}
	}
}

//爆弾の有無判定関数
int Check_coordBomb(char subMap[sizeH][sizeW], int i, int j) {
	//爆弾があるか
	if (subMap[i][j] == 'B') {
		return 1; //爆弾発見
	}
	else {
		return 0; //爆弾なし
	}
}

//サブマップの初期化関数
void Reset_subMap(char subMap[sizeH][sizeW]) {
	//初期化
	Reset_map(subMap);

	int countBomb = 0; //爆弾の個数計測用
	int coordBomb[2] = { 0 }; //爆弾の座標
	while (countBomb < bomb) {
		//座標を生成
		coordBomb[0] = rand() % 10; //爆弾X座標
		coordBomb[1] = rand() % 10; //爆弾Y座標

		//爆弾の位置が重なる場合
		if (subMap[coordBomb[0]][coordBomb[1]] == 'B') {
			continue;
		}

		//爆弾を生成できる場合
		else {
			subMap[coordBomb[0]][coordBomb[1]] = 'B'; //爆弾生成
			countBomb++;

			continue;
		}
	}

	//爆弾の位置情報をマップに記述
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			countBomb = 0;

			//爆弾がない場合
			if (subMap[i][j] != 'B') {
				//上段
				if (i - 1 >= 0) {
					//左上
					if (j - 1 >= 0) {
						countBomb += Check_coordBomb(subMap, i - 1, j - 1);
					}

					//真上
					countBomb += Check_coordBomb(subMap, i - 1, j);

					//右上
					if (j + 1 < sizeW) {
						countBomb += Check_coordBomb(subMap, i - 1, j + 1);
					}
				}

				//中段・左
				if (j - 1 >= 0) {
					countBomb += Check_coordBomb(subMap, i, j - 1);
				}

				//中段・右
				if (j + 1 < sizeW) {
					countBomb += Check_coordBomb(subMap, i, j + 1);
				}

				//下段
				if (i + 1 < sizeH) {
					//左下
					if (j - 1 >= 0) {
						countBomb += Check_coordBomb(subMap, i + 1, j - 1);
					}

					//真下
					countBomb += Check_coordBomb(subMap, i + 1, j);

					//右下
					if (j + 1 < sizeW) {
						countBomb += Check_coordBomb(subMap, i + 1, j + 1);
					}
				}
			}

			//爆弾がある場合
			else {
				continue;
			}

			//個数の記入
			//printf("countBomb = %d\n", countBomb);
			subMap[i][j] = '0' + countBomb;
		}
	}
}

//マップの出力関数
void Output_map(char map[sizeH][sizeW]) {
	printf("\n  0 1 2 3 4 5 6 7 8 9\n");
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

//入力の取得関数：リトライ、終了
char IsGame_continue() {
	while (1) {
		char input = 0;

		printf("\nリトライ：r, 終了：f\n");
		scanf_s("%c", &input, 1);

		//リトライ
		if (input == 'r') {
			Delete_input();
			return input;
		}

		//終了
		else if (input == 'f') {
			Delete_input();
			return input;
		}

		//その他入力
		else {
			printf("\n入力が正しくない\n");
		}
	}
}

//入力の取得関数
int Input_line() {
	while (1) {
		char input = 0;
		int inputFlag = 0; //入力の判定用

		//printf("\n入力(縦座標)：");
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

//ゲームクリア判定関数
int IsGame_clear(char map[sizeH][sizeW], char subMap[sizeH][sizeW]) {
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			//爆弾以外が残っているか
			if (subMap[i][j] != 'B') {
				if (subMap[i][j] != map[i][j]) {
					return 0;
				}
			}
		}
	}

	//ゲームクリア
	return 1;
}

//ゲームの管理関数
int Game_manager(char map[sizeH][sizeW], char subMap[sizeH][sizeW]) {
	Reset_map(map);
	Reset_subMap(subMap);

	while (1) {
		//---------------マップの初期化と表示
		Output_map(map);
		//Output_map(subMap);

		//---------------入力の取得
		int coordX = 0;
		int coordY = 0;

		printf("\n入力(縦座標)：");
		coordY = Input_line();
		//printf("\ncoordX = %d\n", coordX);
		printf("\n入力(横座標)：");
		coordX = Input_line();
		//printf("\ncoordY = %d\n", coordY);

		//-----------------サブマップから爆弾位置の検査
		if (subMap[coordY][coordX] == 'B') {
			//ゲームオーバー
			char temp = 0; //戻り値の取得用 : IsGame_continue

			printf("\nゲームオーバー\n");
			temp = IsGame_continue();

			//リトライ
			if (temp == 'r') {
				return 1;
			}

			//終了
			else {
				return 0;
			}
			
		}
		else {
			//mapに情報を開示
			//printf("\nGame_manager : else\n");
			map[coordY][coordX] = subMap[coordY][coordX];
		}

		//ゲームクリア判定
		int finishFlag = 0; //戻り値の取得用 : IsGame_clear

		if (finishFlag == 0) {
			continue;
		}
		else if(finishFlag == 1) {
			char temp = 0; //戻り値の取得用 : IsGame_continue

			printf("\nゲームクリア\n");
			temp = IsGame_continue();

			//リトライ
			if (temp == 'r') {
				return 1;
			}

			//終了
			else {
				return 0;
			}
		}
	}
}

int main()
{
	//乱数生成用
	srand((unsigned int)time(NULL));

	char map[sizeH][sizeW]; //ゲームマップ
	char subMap[sizeH][sizeW]; //爆弾マップ
	
	int continueFlag = 1;
	while (continueFlag) {
		continueFlag = Game_manager(map, subMap);
	}
	

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
