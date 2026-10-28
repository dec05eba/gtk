/*
 * Copyright © 2016 Red Hat, Inc
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <glib.h>
#include <gio/gio.h>
#include <X11/Xlib.h>

#include "gdkmonitorprivate.h"
#include "gdkscale-x11.h"

#include "gdkx11monitor.h"


struct _GdkX11Monitor
{
  GdkMonitor parent;

  XID output;
  GdkRectangle device_geometry;
  GdkX11Scale scale;
  guint add     : 1;
  guint remove  : 1;
};

struct _GdkX11MonitorClass {
  GdkMonitorClass parent_class;
};

typedef void (* GdkX11MonitorBoundsFunc) (GdkX11Monitor *monitor,
                                          GdkRectangle  *bounds);

void            gdk_x11_monitor_set_device_geometry        (GdkX11Monitor      *monitor,
                                                            const GdkRectangle *geometry,
                                                            const GdkX11Scale  *scale);
void            gdk_x11_monitor_get_device_geometry        (GdkX11Monitor      *monitor,
                                                            GdkRectangle       *geometry);
void            gdk_x11_monitor_get_device_workarea        (GdkX11Monitor      *monitor,
                                                            GdkRectangle       *workarea);

GdkX11Monitor * gdk_x11_display_get_monitor_at_device_rect (GdkDisplay              *display,
                                                            const GdkRectangle      *rect,
                                                            GdkX11MonitorBoundsFunc  get_bounds);

