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

gboolean
cinnamon_settings_get_boolean (CinnamonSettings *settings, const gchar *key)
{
  if (g_settings_check_key_exists(settings->backend, key))
    return g_settings_get_boolean(settings->backend, key);
  else
    return FALSE;
}
