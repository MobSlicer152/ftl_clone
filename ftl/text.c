// text.h implementations

#include "text.h"

// Key-value struct for stb_ds
typedef struct text_kv {
	char *key;
	char *value;
} text_kv_t;

static text_kv_t *texts;

static void load(pkg_file_t *ftl_dat, const char *doc_name);

void text_load(pkg_file_t *ftl_dat, settings_t *settings)
{
	const char *text_names[] = { "achievements", "blueprints", "events",  "misc",
				     "sectorname",   "tooltips",   "tutorial" };
	char *doc_name;
	char *raw;
	size_t i;

	if (!ftl_dat || !settings)
		return;

	FTL_LOG("Loading texts\n");

	// The English texts are in multiple files, but for other languages there's only one file
	if (settings->language == LANGUAGE_ENGLISH) {
		for (i = 0; i < FTL_ARRSIZE(text_names); i++) {
			doc_name = util_strfmt(NULL, "data/text_%s.xml", text_names[i]);
			load(ftl_dat, doc_name);
			stbds_arrfree(doc_name);
		}
	} else {
		// TODO: make enum of language IDs and function to get their names
		//load(ftl_dat, doc_name);
		FTL_LOG("Only English is supported currently\n");
	}
}

static void load(pkg_file_t *ftl_dat, const char *path)
{
	char *raw;
	xmlDoc *doc;
	xmlNode *root;
	xmlNode *cur;
	char *key;
	char *value;

	raw = (char *)pkg_read(ftl_dat, pkg_get(ftl_dat, path));
	doc = xmlParseMemory(raw, stbds_arrlenu(raw));
	root = xmlDocGetRootElement(doc);
	stbds_arrfree(raw);

	for (cur = root->children; cur; cur = cur->next) {
		if (strcmp(cur->name, "text") == 0 && cur->properties && cur->children &&
		    cur->children->type == XML_TEXT_NODE) {
			key = util_strdup(cur->properties->children->content);
			value = util_strdup(cur->children->content);
			stbds_shput(texts, key, value);
		}
	}

	xmlFreeDoc(doc);
}

char *text_get(const char *id)
{
	return stbds_shget(texts, id);
}

void text_cleanup(void)
{
	size_t i;

	for (i = 0; i < stbds_shlenu(texts); i++) {
		if (texts[i].key)
			stbds_arrfree(texts[i].key);
		if (texts[i].value)
			stbds_arrfree(texts[i].value);
	}
	stbds_shfree(texts);
}
