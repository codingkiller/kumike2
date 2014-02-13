#ifndef BUSGPS_DEF
#define BUSGPS_DEF
#include <QtCore/QObject>
class BusGps :public QObject{
	Q_OBJECT
    Q_PROPERTY(QString cur_station READ cur_station NOTIFY curstationChanged)
	Q_PROPERTY(QString next_station READ next_station NOTIFY nextstationChanged)
	Q_PROPERTY(QString cur_station_state READ cur_station_state NOTIFY stationstateChanged)
	Q_PROPERTY(QString left_padding READ left_padding NOTIFY leftPaddingChanged)

public:
	const QString& cur_station_state() const {
		return m_cur_station_state;
	}

	void setCurStationState(const QString& curStationState) {
		m_cur_station_state = curStationState;
	}

	const QString& next_station() const {
		return m_next_station;
	}

	void setNextStation(const QString& nextStation) {
		m_next_station = nextStation;
	}
	const QString& cur_station() const {
			return m_cur_station;
		}

	void setCurStation(const QString& curStation) {
		m_cur_station = curStation;
		emit curstationChanged();
	}
	const QString& left_padding() const {
		return m_leftPadding;
	}

	void setLeftPadding(const QString& leftPadding) {
		m_leftPadding = leftPadding;
		emit leftPaddingChanged();
	}

private :
	QString m_cur_station;
	QString m_next_station;
	QString m_cur_station_state;
	QString m_leftPadding;
Q_SIGNALS:
	void curstationChanged();
	void nextstationChanged();
	void stationstateChanged();
	void leftPaddingChanged();
};
Q_DECLARE_METATYPE(BusGps*)
#endif
