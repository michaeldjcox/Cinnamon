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

GVariant *         cinnamon_settings_get_value (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_value (CinnamonSettings *settings, const gchar *key, GVariant *value);
gboolean           cinnamon_settings_is_writable (CinnamonSettings *settings, const gchar *name);
void               cinnamon_settings_delay (CinnamonSettings *settings);
void               cinnamon_settings_apply (CinnamonSettings *settings);
void               cinnamon_settings_revert (CinnamonSettings *settings);
gboolean           cinnamon_settings_get_has_unapplied (CinnamonSettings *settings);
gboolean           cinnamon_settings_get_boolean (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_boolean (CinnamonSettings *settings, const gchar *key, gboolean value);
gint               cinnamon_settings_get_int (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_int (CinnamonSettings *settings, const gchar *key, gint value);
guint              cinnamon_settings_get_uint (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_uint (CinnamonSettings *settings, const gchar *key, guint value);
gdouble            cinnamon_settings_get_double (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_double (CinnamonSettings *settings, const gchar *key, gdouble value);
gchar *            cinnamon_settings_get_string (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_string (CinnamonSettings *settings, const gchar *key, gchar *value);
gchar **           cinnamon_settings_get_strv (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_strv (CinnamonSettings *settings, const gchar *key, const gchar *const *value);
gint               cinnamon_settings_get_enum (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_enum (CinnamonSettings *settings, const gchar *key, gint value);
guint              cinnamon_settings_get_flags (CinnamonSettings *settings, const gchar *key);
gboolean           cinnamon_settings_set_flags (CinnamonSettings *settings, const gchar *key, guint value);
void               cinnamon_settings_bind (CinnamonSettings *settings,
                                           const gchar *key,
                                           gpointer object,
                                           const gchar *property,
                                           GSettingsBindFlags flags);
void               cinnamon_settings_bind_with_mapping (CinnamonSettings *settings,
                                                        const gchar *key,
                                                        gpointer object,
                                                        const gchar *property,
                                                        GSettingsBindFlags flags,
                                                        GSettingsBindGetMapping get_mapping,
                                                        GSettingsBindSetMapping set_mapping,
                                                        gpointer user_data,
                                                        GDestroyNotify destroy);
void               cinnamon_settings_bind_writable (CinnamonSettings *settings,
                                                    const gchar *key,
                                                    gpointer object,
                                                    const gchar *property,
                                                    gboolean inverted);
void               cinnamon_settings_unbind (gpointer object, const gchar *property);

G_END_DECLS

#endif /* __CINNAMON_SETTINGS_H__ */
