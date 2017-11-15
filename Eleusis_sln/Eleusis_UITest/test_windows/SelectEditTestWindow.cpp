
#include "SelectEditTestWindow.h"
#include <sstream>

using namespace Eleusis;
using namespace Eleusis::Test;
using namespace std;

SelectEditTestWindow::SelectEditTestWindow()
{
    Eleusis::Rectangle* rect = new Eleusis::Rectangle(2000, 1200);
    rect->fillColor_set(Colors::White);
    insertChild(rect);



    /*Rectangle* _diagnostics = new Rectangle(270, 100._FPs);
    _diagnostics->fillColor_set(Colors::AliceBlue());
    _diagnostics->LayoutHost.padding(10, 10, 10, 10);
    insertChild(_diagnostics);

    _diagnosticsText = new TextBlock();
    _diagnosticsText->width_set(250);
    _diagnosticsText->spaceAfter_set(0);
    _diagnosticsText->setText("Diagnostics:\n");
    _diagnostics->insertChild(_diagnosticsText);

    _selectionText2 = new TextBlock();
    _selectionText2->width_set(250);
    _selectionText2->spaceAfter_set(0);
    _selectionText2->LayoutGuest.Classic.top(300);
    _selectionText2->setText("Selection:\n");
    _diagnostics->insertChild(_selectionText2);

    _populateDiagnostics =
        [this](Node* sender, MouseEventArgs* e)
    {
        stringstream l_ss;

        l_ss << "Diagnostics:\n";

        l_ss << "\n";

        l_ss << "Number of lines: " << _se->numberOfShownLines() << "\n";
        l_ss << "Number of shown characters: " << _se->numberOfShownCharacters() << "\n";
        l_ss << "Number of shown unknown characters: " << _se->numberOfShownUnknownCharacters() << "\n";

        l_ss << "\n";

        l_ss << "Character index: " << _se->getCharacterIndex(Vector(e->X, e->Y)) << "\n";

        Rect l_extent = _se->getCharacterExtent(Vector(e->X, e->Y));

        l_ss << "Character extent: \n" 
            << "\tTop: "    << l_extent.lowVector.Y    << "\n"
            << "\tLeft: "   << l_extent.lowVector.X    << "\n"
            << "\tWidth: "  << l_extent.sizeVector().X << "\n"
            << "\tHeight: " << l_extent.sizeVector().Y << "\n";

        _diagnosticsText->setText(l_ss.str());
    };
    */
    

    _se = new SelectEdit();
    
    _se->textSize_set(14);

    Paragraph* l_para1 = new Paragraph("Lorem ŠЋ ipsum dolor sit amet, adipiscing elit.Aenean commodo ligula eget dolor.Aenean massa.Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.");
    Paragraph* l_para2 = new Paragraph("");
    Paragraph* l_para3 = new Paragraph("");
    Paragraph* l_para4 = new Paragraph("");
    Paragraph* l_para5 = new Paragraph("Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. ");

    Paragraph* l_para6 = new Paragraph();
    Span* l_span1 = new Span("Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut,");
    l_span1->foregroundColor_set(Colors::GreenYellow);
    Span* l_span2 = new Span(" imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. ");
    l_span2->foregroundColor_set(Colors::RebeccaPurple);
    Span* l_span3 = new Span("Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. ");
    l_span3->foregroundColor_set(Colors::RoyalBlue);
    Span* l_span4 = new Span("Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim.");
    l_span4->foregroundColor_set(Colors::Teal);
    l_para6->insertSpan(l_span1);
    l_para6->insertSpan(l_span2);
    l_para6->insertSpan(l_span3);
    l_para6->insertSpan(l_span4);

    Paragraph* l_para7 = new Paragraph("Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet.");
    Paragraph* l_para8 = new Paragraph("Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus.");

    _se->insertParagraph(l_para1);
    _se->insertParagraph(l_para2);
    _se->insertParagraph(l_para3);
    _se->insertParagraph(l_para4);
    _se->insertParagraph(l_para5);
    _se->insertParagraph(l_para6);
    _se->insertParagraph(l_para7);
    _se->insertParagraph(l_para8);

    //_se->setText(" ");

    _se->LayoutGuest.Classic.topLeft(50._FPs, 50._FPs);
    _se->LayoutGuest.Classic.anchorTopLeft(50._FPs, 50._FPs);
    _se->width_set(600);

    insertChild(_se);
    
    /*_se2 = new SelectEdit();
    _se2->textSize_set(14);
    _se2->LayoutGuest.Classic.topLeft(30, 300);
    _se2->width_set(600);
    _se2->height_set(600);*/
    //_se2->setText("Winston");
    //insertChild(_se2);


    /*_seleText = new TextBlock();
    _seleText->setText("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. \nDonec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. \nDonec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. \nAliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet.\nQuisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus.");
    _seleText->LayoutGuest.Classic.topLeft(30, 930);
    _seleText->width_set(600);
    //insertChild(_seleText);


    _se->mouseClick += 
        [this](Node* sender, MouseEventArgs* e)
    {
        _populateDiagnostics(sender, e);
    };

    _se->selectingStarted +=
        [this](SelectEdit* sender, EventArgs* e)
    {


    };

    _se->selectionChanged +=
        [this](SelectEdit* sender, EventArgs* e)
    {
        stringstream l_ss;

        l_ss << "Selection Diagnostics:\n";

        l_ss << "\n";
        l_ss << "Selection start: " << _se->getSelectionStart() << "\n";
        l_ss << "Selection end: " << _se->getSelectionEnd() << "\n";
        l_ss << "Caret location: " << _se->getCaretLocation() << "\n";

        _selectionText2->setText(l_ss.str());

        //_seleText->setText(_se->getSelectionText());
    };

    _se->caretChanged +=
        [this](SelectEdit* sender, EventArgs* e)
    {
        stringstream l_ss;

        l_ss << "Selection Diagnostics:\n";

        l_ss << "\n";
        l_ss << "Selection start: " << _se->getSelectionStart() << "\n";
        l_ss << "Selection end: " << _se->getSelectionEnd() << "\n";
        l_ss << "Caret location: " << _se->getCaretLocation() << "\n";

        _selectionText2->setText(l_ss.str());

        //_seleText->setText(_se->getSelectionText());
    };*/
}