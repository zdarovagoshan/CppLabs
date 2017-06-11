#include <conio.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include "user.h"

void main()
{
	using namespace std;
	setlocale(LC_CTYPE, "russian");

	bool exit = false, showMenu=true;
	char input; unsigned __int8 MenuFlags = 0;
	shape *S = NULL;

	romb *sq = NULL;
	SolidRomb *ssq = NULL;
	HollowRomb *hsq = NULL;

	while (!exit)
	{
		if (showMenu) { PrintMenu(MenuFlags); showMenu = false; }
		input = _getch();
		switch (input)
		{
		case '1':	//Задание новой фигуры
		{
			if (S) { S->erase();  S = NULL; } //if (F) delete F;
			if (hsq) { delete hsq; hsq = NULL; }
			if (ssq) { delete ssq; ssq = NULL; }
			if (sq) { delete sq; sq = NULL; }
			MenuFlags = 0;

			cout << "Введите координаты вершин ромба: ";
			POINT s[4];
			cin >> s[0].x >> s[0].y >> s[1].x >> s[1].y >> s[2].x >> s[2].y >> s[3].x >> s[3].y;
			sq = new romb(s);
			cout << "Задайте стиль границы (тип, толщина, цвет RGB): ";
			int t, w; color c;
			cin >> t >> w >> c.r >> c.g >> c.b;
			sq->SetFrameStyle(t, w, c);
			try
			{
				sq->validate();
				MenuFlags |= 0x03;
				cout << "Задать заливку? [Y/N] ";
				input = _getch(); cout << endl;
				if (input == 'y')
				{
					cout << "Задайте стиль заливки (тип, цвет RGB): ";
					cin >> t >> c.r >> c.g >> c.b;
					ssq = new SolidRomb; *ssq = *sq;
					ssq->SetFillStyle(t, c);
					try
					{
						ssq->validate();
						MenuFlags |= 0x04;
						cout << "Задать полую фигуру? [Y/N] ";
						input = _getch(); cout << endl;
						if (input == 'y')
						{
							cout << "Задайте координаты вершин полости: ";
							cin >> s[0].x >> s[0].y >> s[1].x >> s[1].y >> s[2].x >> s[2].y >> s[3].x >> s[3].y;
							hsq = new HollowRomb; *hsq = *ssq;
							hsq->SetInnerFigure(s);
							try
							{
								hsq->validate();
								MenuFlags |= 0x08;
							}
							catch (char *err) { red(); cout << err << endl; plain(); }
						}
					}
					catch (char *err) { red(); cout << err << endl; plain(); }
				}
			}
			catch (char *err) { red(); cout << err << endl; plain(); }
		} break;

		case '2':	//Загрузка новой фигуры
		{
			if (S) { S->erase();  S = NULL; }
			if (hsq) { delete hsq; hsq = NULL; }
			if (ssq) { delete ssq; ssq = NULL; }
			if (sq) { delete sq; sq = NULL; }
			MenuFlags = 0;

			char fname[30];
			cout << "Введите имя файла: "; cin >> fname;
			ifstream fin; fin.open(fname);

			POINT s[4];
			int t, w; color c;
			fin >> s[0].x >> s[0].y >> s[1].x >> s[1].y >> s[2].x >> s[2].y >> s[3].x >> s[3].y >> t >> w >> c.r >> c.g >> c.b;

			sq = new romb(s);
			sq->SetFrameStyle(t, w, c);
			try
			{
				sq->validate();
				MenuFlags |= 0x03;
				if (!fin.eof())
				{
					fin >> t >> c.r >> c.g >> c.b;
					ssq = new SolidRomb; *ssq = *sq;
					ssq->SetFillStyle(t, c);
					try
					{
						ssq->validate();
						MenuFlags |= 0x04;
						if (!fin.eof())
						{

							fin >> s[0].x >> s[0].y >> s[1].x >> s[1].y >> s[2].x >> s[2].y >> s[3].x >> s[3].y;
							hsq = new HollowRomb; *hsq = *ssq;
							hsq->SetInnerFigure(s);
							try
							{
								hsq->validate();
								MenuFlags |= 0x08;
							}
							catch (char *err) { red(); cout << err << endl; plain(); }
						}
					}
					catch (char *err) { red(); cout << err << endl; plain(); }
				}
			}
			catch (char *err) { red(); cout << err << endl; plain(); }
			fin.close();
		} break;

		case '3':	//Изменить фигуру
		{
			if (!(MenuFlags & 0x01))
			{
				red(); cout << "Сперва задайте или загрузите фигуру" << endl;
				plain();
			}
			else
			{
				EditMenu(MenuFlags);
				input = _getch();
				switch (input)
				{
				case '1':
				{
					romb oldsq = *sq;
					cout << "Введите координаты фигуры: ";
					POINT s[4];
					cin >> s[0].x >> s[0].y >> s[1].x >> s[1].y >> s[2].x >> s[2].y >> s[3].x >> s[3].y;
					sq->SetFigure(s);
					cout << "Задайте стиль границы (тип, толщина, цвет RGB): ";
					int t, w; color c;
					cin >> t >> w >> c.r >> c.g >> c.b;
					sq->SetFrameStyle(t, w, c);
					try
					{
						sq->validate();
						if (ssq) *ssq = *sq;
						if (hsq) *hsq = *ssq;
					}
					catch (char *err) { red(); cout << err << endl; plain(); *sq = oldsq; }
				} break;
				case '2':
				{
					int t; color c;
					cout << "Задайте стиль заливки (тип, цвет RGB): ";
					cin >> t >> c.r >> c.g >> c.b;
					if (!ssq) { ssq = new SolidRomb; *ssq = *sq; };
					ssq->SetFillStyle(t, c);
					try
					{
						ssq->validate();
						if (!(MenuFlags & 0x04)) MenuFlags |= 0x04;
						if (hsq) *hsq = *ssq;
					}
					catch (char *err)
					{
						red(); cout << err << endl; plain();
						delete ssq; ssq = NULL; MenuFlags &= 0xFB;
						if (hsq) { delete hsq; hsq = NULL; MenuFlags &= 0xF7; }
					}
				} break;
				case '3':
				{
					if (!(MenuFlags & 0x04))
					{
						red(); cout << "Сперва задайте заливку" << endl;
						plain();
					}
					else
					{
						POINT s[4];
						cout << "Задайте координаты полости: ";
						cin >> s[0].x >> s[0].y >> s[1].x >> s[1].y >> s[2].x >> s[2].y >> s[3].x >> s[3].y;
						if (!hsq) { hsq = new HollowRomb; *hsq = *ssq; }
						hsq->SetInnerFigure(s);
						try
						{
							hsq->validate();
							if (!(MenuFlags & 0x08)) MenuFlags |= 0x08;
						}
						catch (char *err) { red(); cout << err << endl; plain(); delete hsq; hsq = NULL; MenuFlags &= 0xF7; }
					}
				} break;
				case '4': //перемещение фигуры
				{
					try{
						if (S == NULL) throw EMPTY_SLOT;
						int new_x, new_y;
						cout << "Введите координаты перемещения(по Ох и по Оу):\n";
						cin >> new_x >> new_y;
						S->erase();
						S->SetPos(new_x, new_y);
						S->draw();
					}
					catch (char *err) { red();  cout << err << endl; plain(); }
				} break;
				}
			}
		} break;

		case '4':	//Нарисовать контур
		{
			if (!(MenuFlags & 0x02))
			{
				red(); cout << "Сперва задайте или загрузите фигуру" << endl;
				plain();
			}
			else
			{
				if (!S) { S = sq; S->draw(); }
				else { S->erase(); S = sq; S->draw(); }
			}
		} break;


		case '5':	//Нарисовать сплошную фигуру
		{
			if (!(MenuFlags & 0x04))
			{
				red(); cout << "Сперва задайте заливку" << endl;
				plain();
			}
			else
			{
				if (!S) { S = ssq; S->draw(); }
				else { S->erase(); S = ssq; S->draw(); }
			}
		} break;

		case '6':	//Нарисовать полую фигуру
		{
			if (!(MenuFlags & 0x08))
			{
				red(); cout << "Сперва задайте полость фигуры" << endl;
				plain();
			}
			else
			{
				if (!S) { S = hsq; S->draw(); }
				else { S->erase(); S = hsq; S->draw(); }
			}
		} break;

		case '7':	//Сохранение фигуры
		{
			try
			{
				if (S==NULL) throw EMPTY_SLOT;
				char fname[30];
				cout << "Введите имя файла: "; cin >> fname;
				S->save(fname);
			}
			catch (char *err) { red(); cout << err; plain(); }
		} break;

		case 'm': { showMenu = true; } break;

		case 27: { exit = true; } break;	//Выход
		}
	}
}