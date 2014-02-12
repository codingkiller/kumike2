#include "network.hpp"
#include <bb/data/JsonDataAccess>
#include <QtCore/QVariant>
#include <iostream>
using namespace bb::data;
using namespace bb::cascades;

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

void NetworkBus::get_subline_inf(const QString sid){
	QNetworkAccessManager *pNetworkAccessManager = new QNetworkAccessManager(this);
	bool result;
	Q_UNUSED(result);
	result = connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onSublineInfFinished(QNetworkReply*)));
	Q_ASSERT(result);
	QNetworkRequest request = QNetworkRequest();
	m_all_station = subline_inf_url + sid;
	request.setUrl(QUrl(subline_inf_url+sid));
	std::cout << "m_all_station::" << m_all_station.toStdString();
	pNetworkAccessManager->get(request);
}

//! [1]
void NetworkBus::onSublineInfFinished(QNetworkReply* reply){
	if(reply->error() != QNetworkReply::NoError){
		m_buslineText = QString::fromUtf8("网络访问出错，请检查网络后重试！");
	}else{
		JsonDataAccess jda; // at are you
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());
		// TODO if qtData has some error

		const QVariantMap map = qtData.toMap();
		const QString msg = map.values("msg").value(0).toString();
		const QString success = map.values("success").value(0).toString();
		if(success != "true" || msg != "ok"){
			m_buslineText = QString::fromUtf8("网络访问出错，请检查网络后重试！");
			emit buslineChanged();
			this->setProcess(false);
				emit processChanged();
			return;
		}
		const QVariantMap data = map["data"].toMap();
		const QVariantList stations = data["stations"].toList();
		if(stations.isEmpty() || stations.length() == 0){
			m_buslineText = QString::fromUtf8("未查询到线路数据！");
			emit buslineChanged();
			this->setProcess(false);
				emit processChanged();
			return ;
		}
		m_dataModel->clear();
		for(int i=0;i<stations.length();i++){
			const QVariantMap var = stations.at(i).toMap();
			station *sta = new station();
			sta->setCode(var["code"].toString());
			sta->setId(var["id"].toString());
			sta->setLat(var["lat"].toString());
			sta->setLng(var["lng"].toString());
			sta->setName(var["name"].toString());
			if(m_dir == 0)
				startStation->append(sta);
			else endStation->append(sta);

		}
		m_dataModel->append(m_dir == 0 ? *startStation : *endStation);
	}
	qDebug() << "\nm_dataModel size :"<<m_dataModel->size() << "\n";
	this->setProcess(false);
		emit processChanged();
	emit buslineChanged();
}
void NetworkBus::get_lines_by_city(const QString city_id,const QString line_name){
	init();
	this->setProcess(true);
		emit processChanged();
	QNetworkAccessManager *pNetworkAccessManager = new QNetworkAccessManager(this);
	bool result;
	Q_UNUSED(result);
	result = connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onBusLineFinished(QNetworkReply*)));
	Q_ASSERT(result);
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(generateURL(city_id,line_name)));
	pNetworkAccessManager->get(request);
}
void NetworkBus::changeBusLine(int m_dir){
	if(this->m_dir == m_dir)
		return ;
	this->m_dir = m_dir;
	if(startStation->length() > 0 && endStation->length() > 0){
		m_dataModel->clear();
		m_dataModel->append(m_dir == 0 ? *startStation : *endStation);
		return;
	}
	this->setProcess(true);
	emit processChanged();
	this->get_subline_inf(this->getSid());
//	emit buslineChanged();
}

//! [1]
void NetworkBus::onBusLineFinished(QNetworkReply* reply){
	if(reply->error() != QNetworkReply::NoError){
		m_buslineText = QString::fromUtf8("网络访问出错，请检查网络后重试！");
	}else{
		JsonDataAccess jda; // at are you
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());
		// TODO if qtData has some error

		const QVariantMap map = qtData.toMap();
		const QString msg = map.values("msg").value(0).toString();
		const QString success = map.values("success").value(0).toString();
		if(success != "true" || msg != "ok"){
			m_buslineText = QString::fromUtf8("网络访问出错，请检查网络后重试！");
			this->setProcess(true);
			emit processChanged();
			emit buslineChanged();
			return;
		}
		//

		const QVariantList data = map["data"].toList();
		if(data.isEmpty() || data.length() == 0){
			m_buslineText = QString::fromUtf8("未查询到该趟公交车数据！");
			this->setProcess(true);
			emit processChanged();
			emit buslineChanged();
			return ;
		}
		QString result = "";
		for(int i=0;i<data.length();i++){
			const QVariantMap iMap = data.at(i).toMap();
			busline *bus = new busline;
			bus->begin_time = iMap.value("begin_time").toString();
			bus->end_time = iMap.value("end_time").toString();
			bus->id = iMap.value("id").toString();
			bus->start_station = iMap.value("start_station").toString();
			bus->end_station = iMap.value("end_station").toString();
			bus->price = iMap.value("price").toString();
			bus->line_name = iMap.value("line_name").toString();
			bus->isOpen = iMap.value("isopen").toInt();//1
			bus->dir = iMap.value("dir").toInt();//0/1
			if(i == 0)
				startLine = bus;
			else endLine = bus;
		}
		this->get_subline_inf(startLine->id);
	}
//	emit buslineChanged();
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
QString NetworkBus::line_name() const{
	return m_dir == 0 ? startLine->line_name : endLine->line_name;
}
QString NetworkBus::begin_time() const{
	return m_dir ==0 ? startLine->begin_time : endLine->begin_time;
}
QString NetworkBus::end_time() const{
	return m_dir ==0 ? startLine->end_time : endLine->end_time;
}
QString NetworkBus::start_station() const{
	return m_dir ==0 ? startLine->start_station : endLine->start_station;
}
QString NetworkBus::end_station() const{
	return m_dir ==0 ? startLine->end_station : endLine->end_station;
}
QString NetworkBus::price() const{
	return m_dir ==0 ? startLine->price : endLine->price;
}
int NetworkBus::isOpen() const {
	return m_dir ==0 ? startLine->isOpen : endLine->isOpen;
}
int NetworkBus::dir()const{
	return 0;
}
QString NetworkBus::to_station_one()const{
	return startLine->end_station;
}
QString NetworkBus::to_station_two() const {
	return endLine->end_station;
}
QString NetworkBus::all_station() const{
	return m_all_station;
}
bb::cascades::QListDataModel<station*>* NetworkBus::dataModel() const{
	return m_dataModel;
}
