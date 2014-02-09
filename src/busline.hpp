#ifndef BUSLINE_DEF
#define BUSLINE_DEF
#include <QtCore/QObject>

class busline {
public :
	QString city_id;
	QString line_name;
	QString begin_time;
	QString end_time;
	QString start_station;
	QString end_station;
	QString price;
	int isOpen;
	int dir;
	QString id;
};
#endif
