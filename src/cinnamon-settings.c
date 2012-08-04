/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

#include "cinnamon-settings.h"
#include <string.h>

struct _CinnamonSettings
{
  GObject parent;
  
  GSettings *backend;
};

struct _CinnamonSettingsClass
{
  GObjectClass parent_class;
};

enum {
  PROP_0,

  PROP_SETTINGS,
};

G_DEFINE_TYPE(CinnamonSettings, cinnamon_settings, G_TYPE_OBJECT);

/**
 * cinnamon_settings_new:
 *
 * Create a new #CinnamonSettings
 *
 * Return value: The newly created #CinnamonSettings object
 */
CinnamonSettings     *
cinnamon_settings_new (const gchar *schema_id)
{
  CinnamonSettings *settings;
  
  settings = CINNAMON_SETTINGS(g_object_new (CINNAMON_TYPE_SETTINGS, NULL));
  
  settings->backend = g_settings_new(schema_id);

  return settings;
}

static void
cinnamon_settings_finalize (GObject *object)
{
  CinnamonSettings *settings = CINNAMON_SETTINGS (object);

  g_object_unref (settings->backend);

  G_OBJECT_CLASS(cinnamon_settings_parent_class)->finalize (object);
}

static void
cinnamon_settings_get_property(GObject         *object,
                              guint            prop_id,
                              GValue          *value,
                              GParamSpec      *pspec)
{
  CinnamonSettings *settings = CINNAMON_SETTINGS (object);

  switch (prop_id)
    {
    case PROP_SETTINGS:
      g_value_set_object (value, settings->backend);
      break;
    }
}

static void
cinnamon_settings_set_property(GObject         *object,
                          guint            prop_id,
                          const GValue    *value,
                          GParamSpec      *pspec)
{
  //CinnamonSettings *settings = CINNAMON_SETTINGS (object);
  
  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
cinnamon_settings_class_init (CinnamonSettingsClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = cinnamon_settings_finalize;
  gobject_class->get_property = cinnamon_settings_get_property;
  gobject_class->set_property = cinnamon_settings_set_property;
  
  g_object_class_install_property (gobject_class,
                                   PROP_SETTINGS,
                                   g_param_spec_object ("settings",
                                                        "Settings",
                                                        "GSettings backend for CinnamonSettings object",
                                                        G_TYPE_SETTINGS,
                                                        G_PARAM_READABLE));
}

static void
cinnamon_settings_init (CinnamonSettings *settings)
{
  
}

static gboolean
key_contained_in_keys_list (const gchar * const *items,
                            const gchar         *item)
{
  while (*items)
    if (strcmp (*items++, item) == 0)
      return TRUE;

  return FALSE;
}

static gboolean
g_settings_check_key_exists(GSettings *settings, const gchar *key)
{
  gboolean exists;
  gchar **keys_list;

  keys_list = g_settings_list_keys (settings);
  exists = key_contained_in_keys_list ((const gchar **) keys_list, key);
  g_strfreev (keys_list);
  
  if (!exists) g_warning("Key \"%s\" does not exist", key);
  
  return exists;
}

GVariant *
cinnamon_settings_get_value (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_value(settings->backend, key);
  else
    return FALSE;
}

gboolean
cinnamon_settings_set_value (CinnamonSettings *settings, const gchar *key, GVariant *value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_value(settings->backend, key, value);
  else
    return FALSE;
}

gboolean
cinnamon_settings_is_writable (CinnamonSettings *settings, const gchar *name)
{
  if (g_settings_check_key_exists(settings->backend, name))
    return g_settings_is_writable(settings->backend, name);
  else
    return FALSE;
}

void
cinnamon_settings_delay (CinnamonSettings *settings)
{
  g_settings_delay(settings->backend);
}

void
cinnamon_settings_apply (CinnamonSettings *settings)
{
  g_settings_apply(settings->backend);
}

void
cinnamon_settings_revert (CinnamonSettings *settings)
{
  g_settings_revert(settings->backend);
}

gboolean
cinnamon_settings_get_has_unapplied (CinnamonSettings *settings)
{
  return g_settings_get_has_unapplied(settings->backend);
}

gboolean
cinnamon_settings_get_boolean (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_boolean(settings->backend, key);
  else
    return FALSE;
}

gboolean
cinnamon_settings_set_boolean (CinnamonSettings *settings, const gchar *key, gboolean value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_boolean(settings->backend, key, value);
  else
    return FALSE;
}

gint
cinnamon_settings_get_int (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_int(settings->backend, key);
  else
    return 0;
}

gboolean
cinnamon_settings_set_int (CinnamonSettings *settings, const gchar *key, gint value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_int(settings->backend, key, value);
  else
    return FALSE;
}

guint
cinnamon_settings_get_uint (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_uint(settings->backend, key);
  else
    return 0;
}

gboolean
cinnamon_settings_set_uint (CinnamonSettings *settings, const gchar *key, guint value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_uint(settings->backend, key, value);
  else
    return FALSE;
}

gdouble
cinnamon_settings_get_double (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_double(settings->backend, key);
  else
    return 0;
}

gboolean
cinnamon_settings_set_double (CinnamonSettings *settings, const gchar *key, gdouble value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_double(settings->backend, key, value);
  else
    return FALSE;
}

gchar *
cinnamon_settings_get_string (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_string(settings->backend, key);
  else
    return NULL;
}

gboolean
cinnamon_settings_set_string (CinnamonSettings *settings, const gchar *key, gchar *value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_string(settings->backend, key, value);
  else
    return FALSE;
}

/**
 * cinnamon_settings_get_strv:
 * @settings: a #CinnamonSettings object
 * @key: the key to get the value for
 *
 * Wrapper for the g_settings_get_strv function
 *
 * Returns: (array zero-terminated=1) (transfer full): a
 * newly-allocated, %NULL-terminated array of strings, the value that
 * is stored at @key in @settings.
 */
gchar **
cinnamon_settings_get_strv (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_strv(settings->backend, key);
  else
    return NULL;
}

/**
 * cinnamon_settings_set_strv:
 * @settings: a #CinnamonSettings object
 * @key: the name of the key to set
 * @value: (allow-none) (array zero-terminated=1): the value to set it to, or %NULL
 *
 * Sets @key in @settings to @value.
 *
 * Wrapper for the g_settings_set_strv function
 *
 * Returns: %TRUE if setting the key succeeded,
 *     %FALSE if the key was not writable
 */
gboolean
cinnamon_settings_set_strv (CinnamonSettings *settings, const gchar *key, const gchar *const *value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_strv(settings->backend, key, value);
  else
    return FALSE;
}

gint
cinnamon_settings_get_enum (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_enum(settings->backend, key);
  else
    return 0;
}

gboolean
cinnamon_settings_set_enum (CinnamonSettings *settings, const gchar *key, gint value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_enum(settings->backend, key, value);
  else
    return FALSE;
}

guint
cinnamon_settings_get_flags (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_flags(settings->backend, key);
  else
    return 0;
}

gboolean
cinnamon_settings_set_flags (CinnamonSettings *settings, const gchar *key, guint value)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_set_flags(settings->backend, key, value);
  else
    return FALSE;
}

/**
 * cinnamon_settings_bind:
 * @settings: a #CinnamonSettings object
 * @key: the key to bind
 * @object: (type GObject.Object): a #GObject
 * @property: the name of the property to bind
 * @flags: flags for the binding
 *
 * Wrapper for g_settings_bind
 */
void
cinnamon_settings_bind (CinnamonSettings *settings, const gchar *key, gpointer object, const gchar *property, GSettingsBindFlags flags)
{
  if (g_settings_check_key_exists(settings->backend, key))
    g_settings_bind(settings->backend, key, object, property, flags);
}

/**
 * cinnamon_settings_bind_with_mapping: (skip)
 * @settings: a #CinnamonSettings object
 * @key: the key to bind
 * @object: (type GObject.Object): a #GObject
 * @property: the name of the property to bind
 * @flags: flags for the binding
 * @get_mapping: a function that gets called to convert values
 *     from @settings to @object, or %NULL to use the default GIO mapping
 * @set_mapping: a function that gets called to convert values
 *     from @object to @settings, or %NULL to use the default GIO mapping
 * @user_data: data that gets passed to @get_mapping and @set_mapping
 * @destroy: #GDestroyNotify function for @user_data
 *
 * Wrapper for g_settings_bind_with_mapping
 */
void
cinnamon_settings_bind_with_mapping (CinnamonSettings *settings, const gchar *key, gpointer object, const gchar *property, GSettingsBindFlags flags, GSettingsBindGetMapping get_mapping, GSettingsBindSetMapping set_mapping, gpointer user_data, GDestroyNotify destroy)
{
  if (g_settings_check_key_exists(settings->backend, key))
    g_settings_bind_with_mapping (settings->backend, key, object, property, flags, get_mapping, set_mapping, user_data, destroy);
}

void
cinnamon_settings_bind_writable (CinnamonSettings *settings, const gchar *key, gpointer object, const gchar *property, gboolean inverted)
{
  if (g_settings_check_key_exists(settings->backend, key))
    g_settings_bind_writable (settings->backend, key, object, property, inverted);
}
                                                         
void
cinnamon_settings_unbind (gpointer object, const gchar *property)
{
  g_settings_unbind (object, property);
}
