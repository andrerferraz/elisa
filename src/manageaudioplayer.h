/*
 * Copyright 2016 Matthieu Gallien <matthieu_gallien@yahoo.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef MANAGEAUDIOPLAYER_H
#define MANAGEAUDIOPLAYER_H

#include <QObject>
#include <QPersistentModelIndex>
#include <QAbstractItemModel>
#include <QUrl>

class ManageAudioPlayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPersistentModelIndex currentTrack
               READ currentTrack
               WRITE setCurrentTrack
               NOTIFY currentTrackChanged)

    Q_PROPERTY(QAbstractItemModel* playListModel
               READ playListModel
               WRITE setPlayListModel
               NOTIFY playListModelChanged)

    Q_PROPERTY(QUrl playerSource
               READ playerSource
               NOTIFY playerSourceChanged)

    Q_PROPERTY(int urlRole
               READ urlRole
               WRITE setUrlRole
               NOTIFY urlRoleChanged)

    Q_PROPERTY(int isPlayingRole
               READ isPlayingRole
               WRITE setIsPlayingRole
               NOTIFY isPlayingRoleChanged)

    Q_PROPERTY(int playerStatus
               READ playerStatus
               WRITE setPlayerStatus
               NOTIFY playerStatusChanged)

    Q_PROPERTY(int playerPlaybackState
               READ playerPlaybackState
               WRITE setPlayerPlaybackState
               NOTIFY playerPlaybackStateChanged)

    Q_PROPERTY(int playerError
               READ playerError
               WRITE setPlayerError
               NOTIFY playerErrorChanged)

    Q_PROPERTY(int audioDuration
               READ audioDuration
               WRITE setAudioDuration
               NOTIFY audioDurationChanged)

    Q_PROPERTY(bool playerIsSeekable
               READ playerIsSeekable
               WRITE setPlayerIsSeekable
               NOTIFY playerIsSeekableChanged)

    Q_PROPERTY(int playerPosition
               READ playerPosition
               WRITE setPlayerPosition
               NOTIFY playerPositionChanged)

    Q_PROPERTY(int playControlPosition
               READ playControlPosition
               WRITE setPlayControlPosition
               NOTIFY playControlPositionChanged)

    Q_PROPERTY(QVariantMap persistentState
               READ persistentState
               WRITE setPersistentState
               NOTIFY persistentStateChanged)

public:

    enum PlayerStatus {
        NoMedia = 0,
        Loading = NoMedia + 1,
        Loaded = Loading + 1,
        Buffering = Loaded + 1,
        Stalled = Buffering + 1,
        Buffered = Stalled + 1,
        EndOfMedia = Buffered + 1,
        InvalidMedia = EndOfMedia + 1,
        UnknownStatus = InvalidMedia + 1,
    };

    Q_ENUM(PlayerStatus)

    enum PlayerPlaybackState {
        PlayingState = 1,
        PausedState = 2,
        StoppedState = 0,
    };

    Q_ENUM(PlayerPlaybackState)

    enum PlayerErrorState {
        NoError = 0,
        ResourceError = NoError + 1,
        FormatError = ResourceError + 1,
        NetworkError = FormatError + 1,
        AccessDenied = NetworkError + 1,
        ServiceMissing = AccessDenied + 1,
    };

    Q_ENUM(PlayerErrorState)

    explicit ManageAudioPlayer(QObject *parent = 0);

    QPersistentModelIndex currentTrack() const;

    QAbstractItemModel* playListModel() const;

    int urlRole() const;

    int isPlayingRole() const;

    QUrl playerSource() const;

    int playerStatus() const;

    int playerPlaybackState() const;

    int playerError() const;

    int audioDuration() const;

    bool playerIsSeekable() const;

    int playerPosition() const;

    int playControlPosition() const;

    QVariantMap persistentState() const;

    int playListPosition() const;

Q_SIGNALS:

    void currentTrackChanged();

    void playListModelChanged();

    void playerSourceChanged();

    void urlRoleChanged();

    void isPlayingRoleChanged();

    void playerStatusChanged();

    void playerPlaybackStateChanged();

    void playerErrorChanged();

    void playerPlay();

    void playerPause();

    void playerStop();

    void skipNextTrack();

    void audioDurationChanged();

    void playerIsSeekableChanged();

    void playerPositionChanged();

    void playControlPositionChanged();

    void persistentStateChanged();

    void seek(int position);

public Q_SLOTS:

    void setCurrentTrack(const QPersistentModelIndex &currentTrack);

    void setPlayListModel(QAbstractItemModel* aPlayListModel);

    void setUrlRole(int value);

    void setIsPlayingRole(int value);

    void setPlayerStatus(int playerStatus);

    void setPlayerPlaybackState(int playerPlaybackState);

    void setPlayerError(int playerError);

    void ensurePlay();

    void playPause();

    void setAudioDuration(int audioDuration);

    void setPlayerIsSeekable(bool playerIsSeekable);

    void setPlayerPosition(int playerPosition);

    void setPlayControlPosition(int playerPosition);

    void setPersistentState(const QVariantMap &persistentStateValue);

    void playerSeek(int position);

    void playListFinished();

    void tracksDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

private:

    void notifyPlayerSourceProperty();

    void triggerPlay();

    void triggerPause();

    void triggerStop();

    void triggerSkipNextTrack();

    QPersistentModelIndex mCurrentTrack;

    QPersistentModelIndex mOldCurrentTrack;

    QAbstractItemModel *mPlayListModel = nullptr;

    int mUrlRole = Qt::DisplayRole;

    int mIsPlayingRole = Qt::DisplayRole;

    QVariant mOldPlayerSource;

    PlayerStatus mPlayerStatus = NoMedia;

    PlayerPlaybackState mPlayerPlaybackState = StoppedState;

    PlayerErrorState mPlayerError = NoError;

    bool mPlayingState = false;

    bool mSkippingCurrentTrack = false;

    int mAudioDuration = 0;

    bool mPlayerIsSeekable = false;

    int mPlayerPosition = 0;

    bool isFirstPlayTriggerPlay = true;

    bool isFirstPlayTriggerSeek = true;

    QVariantMap mPersistentState;

};

#endif // MANAGEAUDIOPLAYER_H
