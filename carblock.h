#ifndef CARBLOCK_H
#define CARBLOCK_H

#include <QObject>
#include <QtSql>
#include <QQmlListProperty>
#include <QMessageBox>
#include <memory>
#include "bookinginfo.h"
#include "sqldatabase.h"

class BookingInfo;

class CarBlock : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QString brand READ getBrand CONSTANT)
    Q_PROPERTY(QString model READ getModel CONSTANT)
    Q_PROPERTY(QString licensePlate READ getLicensePlate CONSTANT)
    Q_PROPERTY(bool status READ getStatus CONSTANT)
    Q_PROPERTY(QString photoPath READ getPhotoPath CONSTANT)
    Q_PROPERTY(int listIndex READ getListIndex CONSTANT)
    Q_PROPERTY(int mileage READ getMileage CONSTANT)
    Q_PROPERTY(QQmlListProperty<BookingInfo> bookingInfoList READ getBookingInfoList NOTIFY onBookingInfoListChanged)

public:
    enum Status {
        Free,
        Rented,
    };

    explicit CarBlock(const int id = 0,
                      const QString & brand = "Marka",
                      const QString & model = "Model",
                      const QString & licensePlate = "-",
                      bool status = false,
                      const QString & photoPath = "images/car.png",
                      const int mileage = 0,
                      const int listIndex = -1,
                      QObject *parent = 0);

    Q_INVOKABLE const int getId() {return m_id;}
    Q_INVOKABLE const QString getBrand() {return m_brand;}
    Q_INVOKABLE const QString getModel() {return m_model;}
    Q_INVOKABLE const QString getLicensePlate() {return m_licensePlate;}
    Q_INVOKABLE const bool getStatus() {return m_status;}
    Q_INVOKABLE const QString getPhotoPath() {return m_photoPath;}
    Q_INVOKABLE const int getListIndex() {return m_listIndex;}
    Q_INVOKABLE const int getMileage() {return m_mileage;}

    Q_INVOKABLE QQmlListProperty<BookingInfo> getBookingInfoList() {return QQmlListProperty<BookingInfo>(this, nullptr, &bookingInfoListCount, &bookinginfoListAt);}
    static int bookingInfoListCount(QQmlListProperty<BookingInfo>*list);
    static BookingInfo* bookinginfoListAt(QQmlListProperty<BookingInfo> *list, int i);

    Q_INVOKABLE bool isDateReserved(QDate date);
    Q_INVOKABLE bool addToHistory(QVariant entryFields, QString code);
    Q_INVOKABLE bool updateHistory(QVariant entryFields, int distance);
    Q_INVOKABLE bool addToBooking(QVariant entryFields);
    Q_INVOKABLE bool isCodeCorrect(int id, QString code);
    Q_INVOKABLE void readBookingEntries(QDate date, QString time);
    Q_INVOKABLE bool isDateCorrect(QDateTime dateTime);
    Q_INVOKABLE int setHoursColor(QDate date, QString time);
    Q_INVOKABLE int getBookingInfoListSize() {return m_bookingInfoList.size();}

signals:
    void onBookingInfoListChanged(QQmlListProperty<BookingInfo>);

public slots:


private:
    const int m_id;
    const QString m_brand;
    const QString m_model;
    const QString m_licensePlate;
    const bool m_status;
    const QString m_photoPath;
    const int m_listIndex;
    const int m_mileage;
    QSqlQueryModel m_bookingModel;
    QList<BookingInfo*> m_bookingInfoList;
};

#endif // CARBLOCK_H
