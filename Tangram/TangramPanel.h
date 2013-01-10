#ifndef _TANGRAM_PANEL_H_
#define _TANGRAM_PANEL_H_

#include "TangramDlg.h"
#include <wx/event.h>
#include <wx/panel.h>
#include <wx/msgdlg.h>

class TangramPanel : public wxPanel
 {
       public:
            TangramPanel(wxDialog* parent,int id, wxPoint point, wxSize size) : wxPanel(parent,id,point,size), _parent(parent){}
                   
            void mouseMoved(wxMouseEvent& event);
            void mouseDown(wxMouseEvent& event);
            void mouseReleased(wxMouseEvent& event);
        private:
            wxDialog* _parent;
            DECLARE_EVENT_TABLE()
  };



#endif
