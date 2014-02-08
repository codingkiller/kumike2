#include "network.hpp"
#include <bb/data/JsonDataAccess>
#include <QtCore/QVariant>

using namespace bb::data;

QString callbackString(){
	return "&callback=jQuery18209599413950927556_1391823966023&_=1391823975961";
}
QString generateURL( QString city_id,const QString line_name){
	   QString str = busurl;
	   str.append("&city_id="+city_id);
	   str.append("&line_name="+line_name);
	//   str.append(callbackString());
	   return str;
}

void NetworkBus::get_lines_by_city(const QString city_id,const QString line_name){
	QNetworkAccessManager *pNetworkAccessManager = new QNetworkAccessManager(this);
	bool result;
	Q_UNUSED(result);
	result = connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onBusLineFinished(QNetworkReply*)));
	Q_ASSERT(result);
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(generateURL(city_id,line_name)));
	pNetworkAccessManager->get(request);
}
//! [1]
void NetworkBus::onBusLineFinished(QNetworkReply* reply){
	if(reply->error() != QNetworkReply::NoError){
		m_buslineText = QString::fromUtf8("网络访问出错，请检查网络后重试！");
	}else{
	//	m_buslineText = QString::fromUtf8(reply->readAll());
	//	m_buslineText = m_buslineText;
		JsonDataAccess jda;
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());

		const QVariantMap map = qtData.toMap();
		QVariantList data = map["data"].toList();
		QString start_stop = data.at(0).toMap().value("start_station").toString();
	//	QList<QVariant> data = map.values("data");
		//QString start_stop = map["data"].value(0).toString();
		QString msg = map.values("msg").value(0).toString();
		QString success = map.values("success").value(0).toString();
		QString da = qtData.toString();
		m_buslineText = start_stop.append("ok");
	}
	emit buslineChanged();
}


void NetworkBus::reloadData(){
	city_id = "860515";
}

void NetworkBus::changeCity(const QString newCity){
	city_id = newCity;
}


QString NetworkBus::buslineText() const{
	return m_buslineText;
}
