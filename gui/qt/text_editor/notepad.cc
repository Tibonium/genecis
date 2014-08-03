#include "notepad.h"

#define Yes QMessageBox::Yes
#define No QMessageBox::No

// Constructor
notepad::notepad() {
	text_area = new QTextEdit ;
	quitbutton = new QPushButton("&Quit") ;
	
	connect(quitbutton, SIGNAL(clicked()), this, SLOT(quit())) ;
	
	QVBoxLayout* layout = new QVBoxLayout ;
	layout->addWidget(text_area) ;
	layout->addWidget(quitbutton) ;
	
	setLayout(layout) ;
	setWindowTitle(tr("Notepad")) ;
}

// quit check
void notepad::quit() {
	QMessageBox msgbox ;
	msgbox.setWindowTitle(tr("Notepad")) ;
	msgbox.setText(tr("Quit without saving?")) ;
	msgbox.setStandardButtons(Yes | No) ;
	msgbox.setDefaultButton(No) ;
	if( msgbox.exec() == Yes ) {
		qApp->quit() ;
	}
}
