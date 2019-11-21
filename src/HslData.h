/*
 * Copyright (C) 2019 Jolla Ltd.
 * Copyright (C) 2019 Slava Monich <slava@monich.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3. Neither the names of the copyright holders nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * any official policies, either expressed or implied.
 */

#ifndef HSL_DATA_H
#define HSL_DATA_H

#include <gutil_types.h>

#include "HslArea.h"

#include <QtQml>

class HslData : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HslData)
    Q_ENUMS(Language)
    Q_ENUMS(PeriodValidity)
    Q_ENUMS(ValidityLengthType)

public:
    enum Language {
        LanguageUnknown,
        LanguageFinnish,
        LanguageSwedish,
        LanguageEnglish
    };

    enum ValidityLengthType {
        ValidityLengthUnknown,
        ValidityLengthMinute,
        ValidityLengthHour,
        ValidityLength24Hours,
        ValidityLengthDay
    };

    enum PeriodValidity {
        PeriodInvalid = -2,
        PeriodNotYetStarted,
        PeriodEnded,
        PeriodValid
    };

    static const int DATE_BITS = 14;
    static const int TIME_BITS = 11;

    static const QDate START_DATE; // 1.1.1997
    static const QTime START_TIME; // 00:00
    static const QTimeZone HELSINKI_TIMEZONE; // Europe/Helsinki

    HslData(QObject* aParent = Q_NULLPTR);

    // Callback for qmlRegisterSingletonType<HslData>
    static QObject* createSingleton(QQmlEngine*, QJSEngine*);

    Q_INVOKABLE static bool isValidDate(QDate aDate);
    Q_INVOKABLE static bool isValidPeriod(QDate aStart, QDate aEnd);
    static bool isValidTimePeriod(QDateTime aStart, QDateTime aEnd);

    static QDateTime startDateTime(QDate aDate);
    static QDateTime endDateTime(QDate aDate);

    static uint getInt(const GUtilData* aData, uint aOffset, uint aCount);
    static uint getInt(const GUtilData* aData, uint aByteOffset, uint aBitOffset, uint aCount);
    static QDate getDate(const GUtilData* aData, uint aOffset);
    static QDate getDate(const GUtilData* aData, uint aByteOffset, uint aBitOffset);
    static QTime getTime(const GUtilData* aData, uint aOffset);
    static QTime getTime(const GUtilData* aData, uint aByteOffset, uint aBitOffset);
    static HslArea::Type getAreaType(const GUtilData* aData, uint aOffset);
    static HslArea::Type getAreaType(const GUtilData* aData, uint aByteOffset, uint aBitOffset);
    static HslArea getArea(const GUtilData* aData, uint aTypeOffset, uint aAreaOffset);
    static HslArea getArea(const GUtilData* aData, uint aTypeByteOffset, uint aTypeBitOffset,
        uint aAreaByteOffset, uint aAreaBitOffset);
};

QML_DECLARE_TYPE(HslData)

#endif // HSL_DATA_H
