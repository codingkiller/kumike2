#ifndef BUSGPS_DEF
#define BUSGPS_DEF
#include <QtCore/QObject>
class BusGps :public QObject{
public:
	const QString& getCurStationState() const {
		return m_cur_station_state;
	}

	void setCurStationState(const QString& curStationState) {
		m_cur_station_state = curStationState;
	}

	const QString& getNextStation() const {
		return m_next_station;
	}

	void setNextStation(const QString& nextStation) {
		m_next_station = nextStation;
	}
	const QString& getCurStation() const {
			return m_cur_station;
		}

	void setCurStation(const QString& curStation) {
		m_cur_station = curStation;
	}

private:
	Q_OBJECT
    Q_PROPERTY(QString cur_station READ getCurStation NOTIFY curstationChanged)
	Q_PROPERTY(QString next_station READ getNextStation NOTIFY nextstationChanged)
	Q_PROPERTY(QString cur_station_state READ getCurStationState NOTIFY stationstateChanged)

private :
	QString m_cur_station;
	QString m_next_station;
	QString m_cur_station_state;
Q_SIGNALS:
	void curstationChanged();
	void nextstationChanged();
	void stationstateChanged();
};
Q_DECLARE_METATYPE(BusGps*)
#endif
