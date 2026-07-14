/*
 * ct_types.h
 *
 * Copyright 2009-2026
 * Giuseppe Penone <giuspen@gmail.com>
 * Evgenii Gurianov <https://github.com/txe>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <functional>
#include <cstdint>
#include <glibmm/ustring.h>
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/textiter.h>
#include <gtkmm/treeiter.h>
#include <gtkmm/treestore.h>
#include <gtkmm/texttag.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelfilter.h>
#include <gtksourceview/gtksourcebuffer.h>
#include "ct_filesystem.h"

class CtMainWin;
class CtTreeStore;
class CtAnchoredWidget;
class CtImagePng;
class CtImageAnchor;
class CtImageLatex;
class CtImageEmbFile;
class CtCodebox;
class CtTableHeavy;
class CtTableLight;
class CtTableCommon;
class CtExport2Pango;

namespace CtAnchWidgType {
constexpr char ImageAnchor{'a'};
constexpr char ImagePng{'i'};
constexpr char ImageLatex{'l'};
constexpr char CodeBox{'c'};
constexpr char TableHeavy{'t'};
constexpr char TableLight{'T'};
constexpr char ImageEmbFile{'e'};
} // CtAnchWidgType

namespace CtTreeCol {
constexpr int DefTag{'d'};
constexpr int CustomIconId{'c'};
constexpr int Sensitive{'s'};
constexpr int Expanded{'e'};
constexpr int NodeId{'n'};
} // CtTreeCol

enum class CtDocType { XML, SQLite };

enum class CtDocEncrypt { None, False, True };

enum class CtSaveNeedUpdType { None, True, False };

enum class CtLoadFrom { None, File, AfterSave, AfterUpdate };

enum class CtExportType { NONE, PDF, HTML, TXT, CTD, JSONL, HTMLL };

enum class CtTableColMode { None, Add, Delete, MoveLeft, MoveRight };

enum class CtTableRowMode { None, Add, Delete, MoveUp, MoveDown };

enum class CtPangoType { TEXT, BOLD, ITALIC, UNDERLINE, MONOSPACE, SMALL, SUPERSCRIPT, SUBSCRIPT };

enum class CtParseType { RichText, PlainText, ToHtml, ToHtmlList, ToJsonL, ToTxt };

enum class CtLinkType { None, Web, Node, File, Fold, App };

enum class CtDialogDisabled { None, ToolbarConfig, HandleImage, HandleLatex, HandleTable, HandleCodeBox, HandleEmbFile, HandleLink };

enum class CtRestoreExpColl : int { FROM_STR=0, ALL_EXP=1, ALL_COLL=2 };

enum class CtExporting : int { NO=0, FIRST=1, PROCESS=2, LAST=3 };

enum class CtTableSortType : int { ASCII=0, alphaNum=1 };

enum class CtExpandCollapseAll : int { EXPAND=0, COLLAPSE=1 };

enum class CtCurrFileType { None, Shortcut, File };

enum class CtLockGuardState { None, Entered, Leave };

enum class CtTreeState { Tree, TableCell };

enum class CtSearchType { firstFromSel, firstFromTop, all };

enum class CtMatchType { None, Match, AllMatches, BadRegex };

enum class CtAnchMatchType { Range, TableCell };

enum class CtTocEntryType { Plain, Link, TableCell };

enum class CtListType { Number, Bullet, Todo };

enum class CtTreeSortableColumn { Name=0, Addition=1, Modification=2, Custom=3 };

enum class CtPrefDlgTabId { RichText, PlainTextAndCode, Tree, Font, Links, Toolbar, Keyboard, Misc, Theme };

struct CtRecentDocMetadata
{
    std::string   doc_name;
    fs::path      full_path;
    std::time_t   doc_time;
    CtDocEncrypt  encrypt;
    std::string   password;
};

struct CtColumnData
{
    int min{30};
    int max{-1};
    std::string width{100};
};

struct CtTableDimensions
{
    int rows;
    int cols;
};

struct CtStorageNodePending
{
    enum class PendingType { None, Create, Delete, Update, XmlChange, Bookmark };
    PendingType           pending_type{PendingType::None};
    std::set<gint64>      remove_children;
    std::set<std::string> xml_update;
};

struct CtNodeData
{
    gint64         nodeId{-1};
    std::string    name;
    std::string    syntax;
    std::string    tags;
    bool           isReadOnly{false};
    std::time_t    tsCreation{0};
    std::time_t    tsLastSave{0};
    guint16        customIconId{0};
    bool           isBold{false};
    guint16        foregroundRgb24{0};
    guint16        backgroundRgb24{0};
    gint64         sharedNodesMasterId{0};
    std::string    nodeText;
    std::list<CtAnchoredWidget*> anchoredWidgets;
    Glib::RefPtr<Gtk::TextBuffer>  pTextBuffer;
    CtStorageNodePending    pending;
};

struct CtNodeProperties
{
    gint64      nodeId{-1};
    std::string name;
    std::string syntax;
    std::string tags;
    bool        isReadOnly{false};
    std::time_t tsCreation{0};
    std::time_t tsLastSave{0};
    guint16     customIconId{0};
    bool        isBold{false};
    guint16     foregroundRgb24{0};
    guint16     backgroundRgb24{0};
};

struct CtNodeState
{
    gchar       state_type{'n'}; // 'n':node, 'l':leaf
    gint64      nodeId{-1};
    std::string cIter;
    std::string nodeName;
    std::string nodeText;
    guint16     customIconId{0};
    bool        isBold{false};
    guint16     foregroundRgb24{0};
    guint16     backgroundRgb24{0};
    std::string syntax;
    bool        isReadOnly{false};
    std::string tags;
    std::time_t tsCreation{0};
    std::time_t tsLastSave{0};
};

struct CtTreeIter : public Gtk::TreeIter
{
    CtTreeIter() : Gtk::TreeIter() {}
    CtTreeIter(const Gtk::TreeIter& iter) : Gtk::TreeIter(iter) {}
    CtTreeIter(const CtTreeIter& other) : Gtk::TreeIter(other) {}
    CtTreeIter& operator=(const CtTreeIter& other) { (void)Gtk::TreeIter::operator=(other); return *this; }

    gint64            get_node_id_data_holder() const;
    gint64            get_node_parent_id() const;
    gint64            get_node_shared_master_id() const;
    gint64            get_node_children_are_collapsed() const;
    gint64            get_node_brothers_are_collapsed() const;
    std::time_t       get_node_creating_time() const;
    std::time_t       get_node_modification_time() const;
    std::string       get_node_name() const;
    guint16           get_node_custom_icon_id() const;
    bool              get_node_is_bold() const;
    guint16           get_node_foreground_rgb24() const;
    guint16           get_node_background_rgb24() const;
    std::string       get_node_syntax_highlighting() const;
    bool              get_node_read_only() const;
    std::string       get_node_tags() const;
    std::string       get_node_text() const;
    bool              get_node_children_are_on_disk() const;
    std::list<CtAnchoredWidget*> get_anchored_widgets(const int start_offset = -1, const int end_offset = -1);
    std::list<CtAnchoredWidget*> get_anchored_widgets_fast();
    bool              get_node_children_collapsed() const;
    bool              get_node_brothers_collapsed() const;
    void              set_node_name(const std::string& node_name);
    void              set_node_custom_icon_id(const guint16 custom_icon_id);
    void              set_node_is_bold(const bool is_bold);
    void              set_node_foreground_rgb24_custom(const guint16 fg_rgb24);
    void              set_node_background_rgb24_custom(const guint16 bg_rgb24);
    void              set_node_syntax_highlighting(const std::string& syntax_highl);
    void              set_node_read_only(const bool is_read_only);
    void              set_node_tags(const std::string& tags);
    void              set_node_text(const std::string& node_text);
    void              set_node_creating_time(const std::time_t& creating_time);
    void              set_node_modification_time(const std::time_t& mod_time);
    void              pending_new_db_node();
    void              set_node_children_collapsed(const bool val);
    void              set_node_brothers_collapsed(const bool val);
    void              set_node_shared_master_id(const gint64 shared_master_id);
};

struct CtLinkEntry
{
    CtLinkType type{CtLinkType::None};
    std::string webs;
    std::string file;
    std::string fold;
    std::string app;
    gint64 node_id{-1};
    std::string anchor_name;
    std::string f_size;
};

struct CtAnchorExpCollState
{
    bool first{false};
    bool second{false};
};

struct CtTocEntry
{
    int level{0};
    CtTocEntryType type{CtTocEntryType::Plain};
    Glib::ustring text;
    Glib::ustring href;
    int cellRow{0};
    int cellCol{0};
};

struct CtMatchRow
{
    gint64 nodeId{0};
    std::string nodeName;
    gint64 parentId{0};
    std::string lineContent;
    int startOffset{0};
    int endOffset{0};
};

struct CtAnchMatch
{
    int obj_offset{-1};
    CtAnchWidgType anch_type{CtAnchWidgType::ImagePng};
    size_t anch_cell_idx{0};
    int anch_offs_start{-1};
    int anch_offs_end{-1};
};

typedef std::list<CtAnchMatch> CtAnchMatchList;

typedef std::list<CtMatchRow> CtMatchRowList;

struct CtFindOptions
{
    bool case_sensitive{false};
    bool reg_exp{false};
    bool whole_word{false};
    bool start_word{false};
    bool direction_fw{true};
    bool all_matches{false};
    bool node_content{false};
    bool node_name_n_tags{false};
    bool only_sel_n_subnodes{false};
    bool only_bkm_n_subnodes{false};
};

struct CtExportOptions
{
    bool include_node_name{true};
    bool new_node_page{false};
    bool index_in_page{false};
    bool start_collapsed{false};
    bool include_node_tags{true};
};

struct CtStyle
{
    CtStyle(const std::string& style_tag_name, const std::string& style_tag_prop_name, const std::string& style_tag_prop_value)
     : tag_name{style_tag_name}, tag_prop_name{style_tag_prop_name}, tag_prop_value{style_tag_prop_value}
    {}
    std::string tag_name;
    std::string tag_prop_name;
    std::string tag_prop_value;
};

struct CtClipboardData
{
    CtClipboardData(const std::string& rich_, const std::string& plain_, const std::string& html_)
     : rich_text{rich_}, plain_text{plain_}, html_text{html_}
    {}
    std::string rich_text;
    std::string plain_text;
    std::string html_text;
};

struct CtRgb
{
    CtRgb(guint8 r_, guint8 g_, guint8 b_)
     : r{r_}, g{g_}, b{b_}
    {}
    guint8 r;
    guint8 g;
    guint8 b;
};

struct CtScalableTag
{
    CtScalableTag(const char* scale_val, const char* property_name, const char* property_value)
     : scale_val{scale_val}, property_name{property_name}, property_value{property_value}
    {}
    const char* scale_val;
    const char* property_name;
    const char* property_value;
};

struct CtFontUtil
{
    CtFontUtil(guint16 font_size, std::string font_family)
     : font_size{font_size}, font_family{font_family}
    {}
    guint16 font_size;
    std::string font_family;
};

struct CtCodeFontUtil
{
    CtCodeFontUtil(guint16 font_size, std::string font_family)
     : font_size{font_size}, font_family{font_family}
    {}
    guint16 font_size;
    std::string font_family;
};

struct CtCodeExec
{
    CtCodeExec(std::string code_term, std::string code_exec)
     : code_term{code_term}, code_exec{code_exec}
    {}
    std::string code_term;
    std::string code_exec;
};

struct CtPrefDlgState
{
    CtPrefDlgTabId tab_id{CtPrefDlgTabId::RichText};
    std::vector<std::string> shown_tabs;
};

struct CtPasteFrom {
    bool from_other_tree{false};
    bool from_table_column{false};
    bool from_codebox{false};
    CtPasteFrom() {}
};

struct CtSummaryInfo
{
    size_t nodes_rich_text_num{0u};
    size_t nodes_plain_text_num{0u};
    size_t nodes_code_num{0u};
    size_t nodes_shared_tot{0u};
    size_t nodes_shared_groups{0u};
    size_t images_num{0u};
    size_t latexes_num{0u};
    size_t embfile_num{0u};
    size_t heavytables_num{0u};
    size_t lighttables_num{0u};
    size_t codeboxes_num{0u};
    size_t anchors_num{0u};
};

struct CtWordCountInfo
{
    int words{0};
    int chars_with_spaces{0};
    int chars_without_spaces{0};
    int paragraphs{0};
    int lines{0};
};

template<class F> auto scope_guard(F&& f) {
    return std::unique_ptr<void, typename std::decay<F>::type>{(void*)1, std::forward<F>(f)};
}

template <class T, size_t MAX> class ThreadSafeDEQueue
{
public:
    bool push_back(const T& item) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (_queue.size() >= MAX) return false;
        _queue.push_back(item);
        _cond.notify_one();
        return true;
    }
    bool pop_front(T& item) {
        std::unique_lock<std::mutex> lock(_mutex);
        _cond.wait(lock, [this]{return not _queue.empty() or _stop; });
        if (_stop and _queue.empty()) return false;
        item = _queue.front();
        _queue.pop_front();
        return true;
    }
    void stop() {
        std::unique_lock<std::mutex> lock(_mutex);
        _stop = true;
        _cond.notify_all();
    }
private:
    std::deque<T>           _queue;
    std::mutex              _mutex;
    std::condition_variable _cond;
    bool                    _stop{false};
};
