#include <QtGui>

class notepad : public QWidget
{
	Q_OBJECT

	public:
			// constructor
		notepad() ;
	
	private slots:
		void quit() ;
		
	private:
		QTextEdit* text_area ;
		QPushButton* quitbutton ;
};
