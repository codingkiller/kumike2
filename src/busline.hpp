#ifndef BUSLINE_DEF
#define BUSLINE_DEF
#include <QtCore/QObject>

class busline : public QObject{
	Q_OBJECT
    Q_PROPERTY(QString record_id READ getRecordId NOTIFY recordIdChanged)
    Q_PROPERTY(QString search_time READ getSearchTime  NOTIFY recordIdChanged)
	Q_PROPERTY(QString line_name READ getLineName  NOTIFY recordIdChanged)
	Q_PROPERTY(QString start_station READ getStartStation  NOTIFY recordIdChanged)
	Q_PROPERTY(QString end_station READ getEndStation  NOTIFY recordIdChanged)
	Q_PROPERTY(QString city_id READ getCityId  NOTIFY recordIdChanged)
	Q_PROPERTY(QString price READ getPrice  NOTIFY recordIdChanged)
	Q_PROPERTY(QString begin_time READ getBeginTime  NOTIFY recordIdChanged)
	Q_PROPERTY(QString end_time READ getEndTime  NOTIFY recordIdChanged)
	Q_PROPERTY(QString dir READ getDir  NOTIFY recordIdChanged)
	Q_PROPERTY(QString id READ getId  NOTIFY recordIdChanged)
	Q_PROPERTY(QString isOpen READ getIsOpen  NOTIFY recordIdChanged)

Q_SIGNALS:
	void recordIdChanged();
private :
	QString m_city_id;
	QString m_line_name;
	QString m_begin_time;
	QString m_end_time;
	QString m_start_station;
	QString m_end_station;
	QString m_price;
	int m_isOpen;
	int m_dir;
	QString m_id;
	QString m_search_time;
	QString m_record_id;

public:
	const QString& getCityId() const {
			return m_city_id;
	}
	const QString& getLineName() const {
			return m_line_name;
	}
	const QString& getRecordId() const {
			return m_record_id;
	}
	const QString& getStartStation() const {
			return m_start_station;
	}
	const QString& getEndStation() const {
			return m_end_station;
	}
	const QString& getPrice() const {
			return m_price;
	}
	const QString& getSearchTime() const {
			return m_search_time;
	}

	const QString& getBeginTime() const {
		return m_begin_time;
	}

	void setBeginTime(const QString& beginTime) {
		m_begin_time = beginTime;
	}

	void setCityId(const QString& cityId) {
		m_city_id = cityId;
	}

	int getDir() const {
		return m_dir;
	}

	void setDir(int dir) {
		m_dir = dir;
	}

	void setEndStation(const QString& endStation) {
		m_end_station = endStation;
	}

	const QString& getEndTime() const {
		return m_end_time;
	}

	void setEndTime(const QString& endTime) {
		m_end_time = endTime;
	}

	const QString& getId() const {
		return m_id;
	}

	void setId(const QString& id) {
		m_id = id;
	}

	int getIsOpen() const {
		return m_isOpen;
	}

	void setIsOpen(int isOpen) {
		m_isOpen = isOpen;
	}

	void setLineName(const QString& lineName) {
		m_line_name = lineName;
	}

	void setPrice(const QString& price) {
		m_price = price;
	}

	void setRecordId(const QString& recordId) {
		m_record_id = recordId;
	}

	void setSearchTime(const QString& searchTime) {
		m_search_time = searchTime;
	}

	void setStartStation(const QString& startStation) {
		m_start_station = startStation;
	}
};
Q_DECLARE_METATYPE(busline*)
#endif
