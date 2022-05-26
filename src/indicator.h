/*
 *  Copyright 2020-2022 Jesse Lentz
 *
 *  This file is part of iwgtk.
 *
 *  iwgtk is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  iwgtk is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with iwgtk.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _IWGTK_INDICATOR_H
#define _IWGTK_INDICATOR_H

typedef enum {
    INDICATOR_STATION_CONNECTED,
    INDICATOR_STATION_CONNECTING,
    INDICATOR_STATION_DISCONNECTED,
} IndicatorStatus;

typedef struct Indicator_s Indicator;
typedef struct StatusNotifierItem_s StatusNotifierItem;

struct Indicator_s {
    GDBusProxy *proxy;
    GDBusProxy *device_proxy;
    GDBusProxy *adapter_proxy;

    StatusNotifierItem *sni;

    gulong update_device_handler;
    gulong update_adapter_handler;
    gulong update_mode_handler;
    guint signal_agent_id;

    IndicatorStatus status;
    guint8 level;

    Indicator *next;
};

typedef void (*IndicatorSetter) (Indicator *indicator);

Indicator* indicator_new(GDBusProxy *device_proxy);
void indicator_rm(Indicator *indicator);
void indicator_station_init_signal_agent(Indicator *indicator, GDBusProxy *station_proxy);

void indicator_set_device(Indicator *indicator);
void indicator_set_station(Indicator *indicator);
void indicator_set_station_connected(Indicator *indicator);
void indicator_set_ap(Indicator *indicator);
void indicator_set_adhoc(Indicator *indicator);

void indicator_activate(GDBusObject *device_object);
void signal_agent_method_call_handler(GDBusConnection *connection, const gchar *sender, const gchar *object_path, const gchar *interface_name, const gchar *method_name, GVariant *parameters, GDBusMethodInvocation *invocation, Indicator *indicator);

#endif
