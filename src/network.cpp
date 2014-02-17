#include "network.hpp"
#include <bb/data/JsonDataAccess>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <iostream>
using namespace bb::data;
using namespace bb::cascades;

void NetworkBus::get_online_gps(){
	QNetworkAccessManager *pNetworkAccessManager = new QNetworkAccessManager(this);
	bool result;
	Q_UNUSED(result);
	result = connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(get_online_gps_finished(QNetworkReply*)));
	Q_ASSERT(result);
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(get_online_gps_url+m_eid));
	pNetworkAccessManager->get(request);
}

//! [1]
void NetworkBus::get_online_gps_finished(QNetworkReply* reply){
	if(reply->error() != QNetworkReply::NoError){
		m_error = QString::fromUtf8("GPS定位数据请求失败，请稍后重试！");
		onError();
		return ;
	}else{
		JsonDataAccess jda; // at are you
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());
		const QVariantMap map = qtData.toMap();

		const QVariantList records = map["records"].toList();
	//	const QVariantList stations = data["stations"].toList();
		if(records.isEmpty()){
			m_error = QString::fromUtf8("未查询到GPS数据！");
			onError();
			return ;
		}
		for(int i=0;i<m_dataModel->size()-1;i++){

			for(int j = 0 ; j < records.length();j++){
				const QStringList var = records.at(j).toStringList();
				const QString cur_station_state = var[19];
				const QString next_station = var[17];
				const QString cur_station = var[18];
				const QString subline_ids = var[20];
				if(subline_id() != subline_ids) continue;
			//	float leftPadding = 0;
				if(cur_station == m_dataModel->value(i)->name() && next_station == m_dataModel->value(i+1)->name()){
					if(cur_station_state != "2"){//显示在站点
						m_dataModel->value(i)->setBusState("cur_station");
					}
					else{//显示正中间
						m_dataModel->value(i)->setBusState("middle");
					}
				}
			}
		}
	//	m_dataModel->append(m_dir == 0 ? *startStation : *endStation);
	}
//	qDebug() << "\nm_dataModel size :"<<m_dataModel->size() << "\n";
	setProcess(false);
	emit processChanged();
	emit busstateChanged();
//	this->get_lineisopen();
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
		m_error = QString::fromUtf8("站点信息请求失败，请检查网络后重试！");
		onError();
		return ;
	}else{
		JsonDataAccess jda; // at are you
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());
		// TODO if qtData has some error

		const QVariantMap map = qtData.toMap();
		const QString msg = map.values("msg").value(0).toString();
		const QString success = map.values("success").value(0).toString();
		if(success != "true" || msg != "ok"){
			m_error = QString::fromUtf8("站点信息返回不成功，请稍后重试！");
			onError();
			return;
		}
		const QVariantMap data = map["data"].toMap();
		const QVariantList stations = data["stations"].toList();
		if(stations.isEmpty() || stations.length() == 0){
			m_error = QString::fromUtf8("未查询到站点数据！");
			onError();
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
		//	QString name = QString::number(i+1) ;
		//	name.append(var["name"].toString());
			sta->setIndex(QString::number(i+1));
		//	qDebug() << "name string : " << name ;
			sta->setName(var["name"].toString());
			if(m_dir == 0)
				startStation->append(sta);
			else endStation->append(sta);
		}
		m_dataModel->append(m_dir == 0 ? *startStation : *endStation);
	}
	qDebug() << "\nm_dataModel size :"<<m_dataModel->size() << "\n";
	emit dataModelChanged();
	emit buslineChanged();
	this->get_lineisopen();
}
void NetworkBus::get_lineisopen(){
	QNetworkAccessManager *pNetworkAccessManager = new QNetworkAccessManager(this);
	bool result;
	Q_UNUSED(result);
	result = connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onLineIsOpenFinished(QNetworkReply*)));
	Q_ASSERT(result);
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(t_lineisopen_url+m_city_id+"&line="+line_name()));
	pNetworkAccessManager->get(request);
}
void NetworkBus::onLineIsOpenFinished(QNetworkReply* reply){
	if(reply->error() != QNetworkReply::NoError){
		m_error = QString::fromUtf8("线路开通数据请求错误，请检查网络后重试！");
		onError();
		return;
	}else{
		JsonDataAccess jda; // at are you
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());
		// TODO if qtData has some error

		const QVariantMap map = qtData.toMap();
		const QString msg = map.values("msg").value(0).toString();
		const QString success = map.values("success").value(0).toString();
		if(success != "true" || msg != "ok"){
			m_error = QString::fromUtf8("线路开通返回失败，请检查网络后重试！");
			onError();
			return;
		}
		const QVariantList data = map["data"].toList();
		m_eid = data.at(0).toMap().value("eid").toString();
		m_isopen = data.at(0).toMap().value("isopen").toInt();
		qDebug() << "isOpen:" << m_isopen << "  eid:" << m_eid << "\n";
		this->get_online_gps();
	}
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
	m_city_id = city_id;
	request.setUrl(QUrl(get_lines_by_city_url+city_id+"&line_name="+line_name.toUpper()));
	pNetworkAccessManager->get(request);
}
void NetworkBus::deleteRecord(const int record_id){
		    	bool result = dbService->deleteRecord(record_id);
		    	if(result){
		    		qDebug() << "delete data record_id :" << record_id << " finished ";
		    	//	dbService->readRecords();
		    	//	emit localDataModelChanged();
		    	}
		    }
void NetworkBus::changeBusLine(int m_dir){
	if(this->m_dir == m_dir)
		return ;
	this->m_dir = m_dir;
	if(startStation->length() > 0 && endStation->length() > 0){
		emit buslineChanged();
		m_dataModel->clear();
		m_dataModel->append(m_dir == 0 ? *startStation : *endStation);
		this->setProcess(true);
		emit processChanged();
		this->get_online_gps();
		return;
	}
	this->setProcess(true);
	emit processChanged();
	this->get_subline_inf(this->getSid());
//	emit buslineChanged();
}
void NetworkBus::reloadGPSData(){
//		m_dataModel->clear();
//		m_dataModel->append(m_dir == 0 ? *startStation : *endStation);
		this->setProcess(true);
		emit processChanged();
		this->get_online_gps();
}
//! [1]
void NetworkBus::onBusLineFinished(QNetworkReply* reply){
	if(reply->error() != QNetworkReply::NoError){
		m_error = QString::fromUtf8("线路数据请求错误，请检查网络后重试！");
		onError();
		return;
	}else{
		JsonDataAccess jda; // at are you
		const QVariant qtData = jda.loadFromBuffer(reply->readAll());
		// TODO if qtData has some error

		const QVariantMap map = qtData.toMap();
		const QString msg = map.values("msg").value(0).toString();
		const QString success = map.values("success").value(0).toString();
		if(success != "true" || msg != "ok"){
			m_error = QString::fromUtf8("线路数据返回不成功，请检查网络后重试！");
			onError();
			return;
		}
		//

		const QVariantList data = map["data"].toList();
		if(data.isEmpty() || data.length() == 0){
			m_error = QString::fromUtf8("未查询到该趟公交车数据！");
			onError();
			return ;
		}
		QString result = "";
		for(int i=0;i<data.length();i++){
			const QVariantMap iMap = data.at(i).toMap();
			busline *bus = new busline;
			bus->setBeginTime(iMap.value("begin_time").toString());
			bus->setEndTime(iMap.value("end_time").toString());
			bus->setId(iMap.value("id").toString());
			bus->setStartStation(iMap.value("start_station").toString());
			bus->setEndStation(iMap.value("end_station").toString());
			bus->setPrice(iMap.value("price").toString());
			bus->setLineName(iMap.value("line_name").toString());
			bus->setIsOpen(iMap.value("isopen").toInt());//1
			bus->setDir(iMap.value("dir").toInt());//0/1
			bus->setCityId(m_city_id);
			if(iMap.value("dir").toInt() == 0){
				int record_id = dbService->findRecordId(m_city_id,bus->getLineName());
				if(record_id != 0){
					dbService->updateRecord(record_id);
				}else{
					dbService->createRecord(bus);
				}
				dbService->readRecords(m_city_id);
				emit localDataModelChanged();
				startLine = bus;
			}
			else endLine = bus;
		}
		this->get_subline_inf(startLine->getId());
	}
	emit buslineChanged();
}


void NetworkBus::reloadData(){
	m_city_id = "860515";
}

void NetworkBus::changeCity(const QString newCity){
	m_city_id = newCity;
}

QString NetworkBus::error() const{
	return m_error;
}
QString NetworkBus::line_name() const{
	return m_dir == 0 ? startLine->getLineName() : endLine->getLineName();
}
QString NetworkBus::begin_time() const{
	return m_dir ==0 ? startLine->getBeginTime() : endLine->getBeginTime();
}
QString NetworkBus::end_time() const{
	return m_dir ==0 ? startLine->getEndTime() : endLine->getEndTime();
}
QString NetworkBus::start_station() const{
	return m_dir ==0 ? startLine->getStartStation() : endLine->getStartStation();
}
QString NetworkBus::end_station() const{
	return m_dir ==0 ? startLine->getEndStation() : endLine->getEndStation();
}
QString NetworkBus::price() const{
	return m_dir ==0 ? startLine->getPrice() : endLine->getPrice();
}
int NetworkBus::isOpen() const {
	return m_dir ==0 ? startLine->getIsOpen() : endLine->getIsOpen();
}
int NetworkBus::dir()const{
	return 0;
}
QString NetworkBus::to_station_one()const{
	return startLine->getEndStation();
}
QString NetworkBus::to_station_two() const {
	return endLine->getEndStation();
}

bb::cascades::QListDataModel<station*>* NetworkBus::dataModel() const{
	return m_dataModel;
}
/*bb::cascades::QListDataModel<BusGps*>* NetworkBus::gpsDataModel() const{
	return m_gpsDataModel;
}*/
