/** -*- Mode: c++ -*-
 *  IPTVChannel
 *  Copyright (c) 2006-2009 Silicondust Engineering Ltd, and
 *                          Daniel Thor Kristjansson
 *  Copyright (c) 2012 Digital Nirvana, Inc.
 *  Copyright (c) 2013 Bubblestuff Pty Ltd
 *  Distributed as part of MythTV under GPL v2 and later.
 */

#ifndef _IPTV_CHANNEL_H_
#define _IPTV_CHANNEL_H_

// Qt headers
#include <QMutex>

// MythTV headers
#include "dtvchannel.h"
#include "iptvstreamhandler.h"

class IPTVTuningData;
class IPTVRecorder;
class MPEGStreamData;

class IPTVChannel : QObject, public DTVChannel
{
    Q_OBJECT
    friend class IPTVRecorder;

  public:
    IPTVChannel(TVRec*, const QString&);
    ~IPTVChannel();

    // Commands
    virtual bool Open(void);

    using DTVChannel::Tune;
    virtual bool Tune(const IPTVTuningData&, bool scanning);
    virtual bool Tune(const DTVMultiplex&, QString) { return false; }

    // Sets
    void SetStreamData(MPEGStreamData*);

    // Gets
    bool IsOpen(void) const;
    virtual QString GetDevice(void) const
        { return m_last_tuning.GetDeviceKey(); }
    IPTVStreamHandler *GetStreamHandler(void) const { return m_stream_handler; }
    virtual bool IsIPTV(void) const { return true; } // DTVChannel
    virtual bool IsPIDTuningSupported(void) const { return true; }

  protected:
    virtual void Close(void);
    bool EnterPowerSavingMode(void);
    virtual bool IsExternalChannelChangeSupported(void) { return true; }

  private:
    void OpenStreamHandler(void);
    void CloseStreamHandler(void);

  private:
    mutable QMutex     m_tune_lock;
    volatile bool      m_firsttune;
    IPTVTuningData     m_last_tuning;
    mutable QMutex     m_stream_lock;
    IPTVStreamHandler *m_stream_handler;
    MPEGStreamData    *m_stream_data;
    QString            m_videodev;
};

#endif // _IPTV_CHANNEL_H_

/* vim: set expandtab tabstop=4 shiftwidth=4: */
