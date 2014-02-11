#include "station.hpp"

	void station::setCode(const QString& code) {
		m_code = code;
		emit codeChanged();
	}

	void station::setId(const QString& id) {
		m_id = id;
	}

	void station::setLat(const QString& lat) {
		m_lat = lat;
	}

	void station::setLng(const QString& lng) {
		m_lng = lng;
	}

	void station::setName(const QString& name) {
		m_name = name;
		emit nameChanged();
	}

	const QString& station::code() const {
		return m_code;
	}

	const QString& station::id() const {
		return m_id;
	}

	const QString& station::lat() const {
		return m_lat;
	}

	const QString& station::lng() const {
		return m_lng;
	}

	const QString& station::name() const {
		return m_name;
	}
