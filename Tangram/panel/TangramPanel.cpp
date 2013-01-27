#include "TangramPanel.h"

BEGIN_EVENT_TABLE(TangramPanel, wxPanel)

 EVT_MOTION(TangramPanel::mouseMoved)
 EVT_LEFT_DOWN(TangramPanel::mouseDown)
 EVT_LEFT_UP(TangramPanel::mouseReleased)
 EVT_LEFT_DCLICK(TangramPanel::mouseLeftDoubleClick)
 EVT_RIGHT_DOWN(TangramPanel::mouseRightClick)
 
END_EVENT_TABLE()

void TangramPanel::mouseMoved(wxMouseEvent& event)
{
    TangramDlg* parent=dynamic_cast<TangramDlg*>(_parent);
    parent->MouseMoved(event);

}
void TangramPanel::mouseDown(wxMouseEvent& event)
{
    TangramDlg* parent=dynamic_cast<TangramDlg*>(_parent);
    parent->MouseLeftDown(event);
    
}
void TangramPanel::mouseReleased(wxMouseEvent& event)
{
    TangramDlg* parent=dynamic_cast<TangramDlg*>(_parent);
    parent->MouseLeftUp(event); 
}

void TangramPanel::mouseLeftDoubleClick(wxMouseEvent& event)
{
    TangramDlg* parent=dynamic_cast<TangramDlg*>(_parent);
    parent->MouseLeftDoubleClick(event); 
}

void TangramPanel::mouseRightClick(wxMouseEvent& event)
{
    TangramDlg* parent=dynamic_cast<TangramDlg*>(_parent);
    parent->MouseRightClick(event); 
}
