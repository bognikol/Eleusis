#include "CoordinatesTestWindow.h"

using namespace std;
using namespace Eleusis;

CoordinatesTestWindow::CoordinatesTestWindow()
{
    vector<vector<Eleusis::Rectangle*>> rect (Y_num, vector<Eleusis::Rectangle*>(X_num));

    for (int i = 0; i <= Y_num - 1; i++)
    {
        for (int j = 0; j <= X_num - 1; j++)
        {
            rect[i][j] = new Eleusis::Rectangle(50, 50);
            rect[i][j]->LayoutGuest.Classic.top(100 * i);
            rect[i][j]->LayoutGuest.Classic.left(100 * j);
            rect[i][j]->fillBrush_set(shared_ptr<SolidColorBrush>(new SolidColorBrush(255 / X_num * i, 255 / Y_num * j, 255)));
            insertChild(rect[i][j]);
        }
    }

}
