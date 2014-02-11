#ifndef STATION_DEF
#define STATION_DEF
#include <QtCore/QObject>
class station :public QObject{
	Q_OBJECT
    // These are the properties that will be accessible by the datamodel in the view.
    Q_PROPERTY(QString code READ code NOTIFY codeChanged)
	Q_PROPERTY(QString name READ name NOTIFY nameChanged)
	Q_PROPERTY(QString lat READ lat NOTIFY nameChanged)
	Q_PROPERTY(QString lng READ lng NOTIFY nameChanged)
	Q_PROPERTY(QString id READ id NOTIFY nameChanged)

private :
	QString m_code;
	QString m_lat;
	QString m_lng;
	QString m_name;
	QString m_id;

public:
/*	~station(){}
	virtual station(){}*/
/*	station(QObject *parent = 0)
	    : QObject(parent)
	{
	}
	station(const QString &id, const QString &name, const QString &code,const QString &lat,const QString &lng, QObject *parent = 0)
	    : QObject(parent)
	    , m_id(id)
	    , m_name(name)
	    , m_code(code)
	, m_lat(lat)
	, m_lng(lng)
	{
	}*/
	void setCode(const QString& code);

	void setId(const QString& id);

	void setLat(const QString& lat);

	void setLng(const QString& lng);

	void setName(const QString& name);

	const QString& code() const;

	const QString& id() const;

	const QString& lat() const;

	const QString& lng() const;

	const QString& name() const;
	Q_SIGNALS:
		void codeChanged();
		void nameChanged();
};
Q_DECLARE_METATYPE(station*)
#endif
