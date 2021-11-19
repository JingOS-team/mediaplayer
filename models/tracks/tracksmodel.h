/*
 * Copyright (C) 2021 Beijing Jingling Information System Technology Co., Ltd. All rights reserved.
 *
 * Authors:
 * Yu Jiashu <yujiashu@jingos.com>
 *
 */

#ifndef TRACKSMODEL_H
#define TRACKSMODEL_H

#include <QObject>
#include <QVariant>

#ifdef STATIC_MAUIKIT
#include "fmh.h"
#include "mauilist.h"
#else
#include <MauiKit/fmh.h>
#include <MauiKit/mauilist.h>
#endif

#include <klocalizedstring.h>

class CollectionDB;
class TracksModel : public MauiList
{
    Q_OBJECT
    Q_PROPERTY(QString query READ getQuery WRITE setQuery NOTIFY queryChanged())
    Q_PROPERTY(TracksModel::SORTBY sortBy READ getSortBy WRITE setSortBy NOTIFY sortByChanged)

public:

    enum SORTBY : uint_fast8_t
    {
        ADDDATE = FMH::MODEL_KEY::ADDDATE,
        RELEASEDATE = FMH::MODEL_KEY::RELEASEDATE,
        FORMAT = FMH::MODEL_KEY::FORMAT,
        ARTIST = FMH::MODEL_KEY::ARTIST,
        TITLE = FMH::MODEL_KEY::TITLE,
        ALBUM = FMH::MODEL_KEY::ALBUM,
        RATE = FMH::MODEL_KEY::RATE,
        FAV = FMH::MODEL_KEY::FAV,
        TRACK = FMH::MODEL_KEY::TRACK,
        COUNT = FMH::MODEL_KEY::COUNT,
        NONE

    }; Q_ENUM(SORTBY)

    explicit TracksModel(QObject *parent = nullptr);

    void componentComplete() override final;

    const FMH::MODEL_LIST &items() const override;

    void setQuery(const QString &query);
    QString getQuery() const;

    void setSortBy(const TracksModel::SORTBY &sort);
    TracksModel::SORTBY getSortBy() const;
    QVariantMap currentTrack() const;
    int currentIndex() const;

private:
    CollectionDB *db;
    FMH::MODEL_LIST list;
    QVariantMap m_currentTrack;
    int m_currentIndex;

    void sortList();
    void setList();

    QString query;
    TracksModel::SORTBY sort = TracksModel::SORTBY::ADDDATE;

signals:
    void queryChanged();
    void sortByChanged();
    void currentIndexChanged(int currentIndex);
    void currentTrackChanged(QVariantMap currentTrack);
    void nextRequest();
    void previousRequest();

public slots:
    QVariantMap get(const int &index) const;
    QVariantList getAll();
    void append(const QVariantMap &item);
    void justAppend(const QVariantMap &item);
    void appendRefresh();
    void append(const QVariantMap &item, const int &at);
    void appendQuery(const QString &query);
    void searchQueries(const QStringList &queries, const int &type);
    void clear();
    bool color(const int &index, const QString &color);
    bool fav(const int &index, const bool &value);
    bool rate(const int &index, const int &value);
    bool countUp(const int &index, const bool &value);
    bool remove(const int &index);
    void refresh();
    bool update(const QVariantMap &data, const int &index);

    bool deleteFile(const int &index);
    void deleteFiles(const QList<QUrl> &urls);
    bool copyFile(const int &index, const bool &value);

    void emitpPlayingState(const bool &isPlay);
};

#endif // TRACKSMODEL_H
