#include "TangramPanel.h"

BEGIN_EVENT_TABLE(TangramPanel, wxPanel)

 EVT_MOTION(TangramPanel::mouseMoved)
 EVT_LEFT_DOWN(TangramPanel::mouseDown)
 EVT_LEFT_UP(TangramPanel::mouseReleased)
 
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
