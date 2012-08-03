/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
#ifndef __CINNAMON_SETTINGS_H__
#define __CINNAMON_SETTINGS_H__

#include <gio/gio.h>

G_BEGIN_DECLS

/**
 * SECTION:CinnamonSettings
 * short_description: Blop
 *
 * Blopblop
 */
typedef struct _CinnamonSettings      CinnamonSettings;
typedef struct _CinnamonSettingsClass CinnamonSettingsClass;

#define CINNAMON_TYPE_SETTINGS              (cinnamon_settings_get_type ())
#define CINNAMON_SETTINGS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), CINNAMON_TYPE_SETTINGS, CinnamonSettings))
#define CINNAMON_SETTINGS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), CINNAMON_TYPE_SETTINGS, CinnamonSettingsClass))
#define CINNAMON_IS_SETTINGS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), CINNAMON_TYPE_SETTINGS))
#define CINNAMON_IS_SETTINGS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), CINNAMON_TYPE_SETTINGS))
#define CINNAMON_SETTINGS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), CINNAMON_TYPE_SETTINGS, CinnamonSettingsClass))

GType              cinnamon_settings_get_type     (void) G_GNUC_CONST;

CinnamonSettings*  cinnamon_settings_new (const gchar *schema_id);

gboolean           cinnamon_settings_get_boolean (CinnamonSettings *settings, const gchar *key);

G_END_DECLS

#endif /* __CINNAMON_SETTINGS_H__ */
