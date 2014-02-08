#ifndef Network_BUS_
#define Network_BUS_
#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

class NetworkBus : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString buslineText READ buslineText NOTIFY buslineChanged)

	private:
		QString city_id;
		QString line_name;
		QString m_buslineText;
	public Q_SLOTS:
		void onBusLineFinished(QNetworkReply* reply);
		void get_lines_by_city(const QString city_id,const QString line_name);
		void changeCity(const QString newCity);

//		NetworkBus();
	public:
//		~NetworkBus();
		void reloadData();
		void locateBus();

		QString buslineText() const;

		Q_SIGNALS:
			void buslineChanged();

};
const static QString busurl = "http://busi.gpsoo.net/v1/bus/get_lines_by_city?type=handset";

#endif
