/********************************************************************\
 * qofquerycore.h -- API for providing core Query data types           *
 * Copyright (C) 2002 Derek Atkins <warlord@MIT.EDU>                *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652       *
 * Boston, MA  02111-1307,  USA       gnu@gnu.org                   *
 *                                                                  *
\********************************************************************/

/** @file qofquerycore.h
    @breif API for providing core Query data types
    @author Copyright (C) 2002 Derek Atkins <warlord@MIT.EDU>
*/

#ifndef QOF_QUERYCORE_H
#define QOF_QUERYCORE_H

#include <glib.h>

#include "gnc-numeric.h"
#include "gnc-date.h"
#include "kvp_frame.h"
#include "qofclass.h"

typedef struct _QofQueryPredData QofQueryPredData;

/** Standard Query comparitors, for how to compare objects in a predicate.
 *  Note that not all core types implement all comparitors
 */
typedef enum {
  QOF_COMPARE_LT = 1,
  QOF_COMPARE_LTE,
  QOF_COMPARE_EQUAL,
  QOF_COMPARE_GT,
  QOF_COMPARE_GTE,
  QOF_COMPARE_NEQ
} QofQueryCompare;

/** List of known core query data-types... 
 *  Each core query type defines it's set of optional "comparitor qualifiers".
 */
/* Comparisons for QOF_TYPE_STRING */
typedef enum {
  QOF_STRING_MATCH_NORMAL = 1,
  QOF_STRING_MATCH_CASEINSENSITIVE
} QofStringMatch;

/* Comparisons for QOF_TYPE_DATE	*/
typedef enum {
  QOF_DATE_MATCH_NORMAL = 1,
  QOF_DATE_MATCH_ROUNDED
} QofDateMatch;

/* Comparisons for QOF_TYPE_NUMERIC, QOF_TYPE_DEBCRED	*/
typedef enum {
  QOF_NUMERIC_MATCH_DEBIT = 1,
  QOF_NUMERIC_MATCH_CREDIT,
  QOF_NUMERIC_MATCH_ANY
} QofNumericMatch;

/* Comparisons for QOF_TYPE_GUID */
typedef enum {
  /** These expect a single object and expect the 
   * QofAccessFunc returns GUID* */
  QOF_GUID_MATCH_ANY = 1,
  QOF_GUID_MATCH_NONE,
  QOF_GUID_MATCH_NULL,
  /** These expect a GList* of objects and calls the QofAccessFunc routine
   * on each item in the list to obtain a GUID* for each object */
  QOF_GUID_MATCH_ALL,
  /** These expect a single object and expect the QofAccessFunc function
   * to return a GList* of GUID* (the list is the property of the caller) */
  QOF_GUID_MATCH_LIST_ANY,
} QofGuidMatch;

/** No extended comparisons for QOF_TYPE_INT32, QOF_TYPE_INT64,
 *  QOF_TYPE_DOUBLE, QOF_TYPE_BOOLEAN, QOF_TYPE_KVP
 */

/** A CHAR type is for a RECNCell */
/* Comparisons for QOF_TYPE_CHAR */
typedef enum {
  QOF_CHAR_MATCH_ANY = 1,
  QOF_CHAR_MATCH_NONE
} QofCharMatch;

/** Head of Predicate Data structures.  All PData must start like this. */
struct _QofQueryPredData {
  QofType               type_name;  /* QOF_TYPE_* */
  QofQueryCompare       how;
};


/** Core Data Type Predicates */
QofQueryPredData *qof_query_string_predicate (QofQueryCompare how, char *str,
					 QofStringMatch options,
					 gboolean is_regex);
QofQueryPredData *qof_query_date_predicate (QofQueryCompare how,
				       QofDateMatch options, Timespec date);
QofQueryPredData *qof_query_numeric_predicate (QofQueryCompare how,
					  QofNumericMatch options,
					  gnc_numeric value);
QofQueryPredData *qof_query_guid_predicate (QofGuidMatch options, GList *guids);
QofQueryPredData *qof_query_int32_predicate (QofQueryCompare how, gint32 val);
QofQueryPredData *qof_query_int64_predicate (QofQueryCompare how, gint64 val);
QofQueryPredData *qof_query_double_predicate (QofQueryCompare how, double val);
QofQueryPredData *qof_query_boolean_predicate (QofQueryCompare how, gboolean val);
QofQueryPredData *qof_query_char_predicate (QofCharMatch options,
				       const char *chars);
QofQueryPredData *qof_query_kvp_predicate (QofQueryCompare how,
				      GSList *path, const KvpValue *value);

/** Copy a predicate. */
QofQueryPredData *qof_query_core_predicate_copy (QofQueryPredData *pdata);

/** Destroy a predicate. */
void qof_query_core_predicate_free (QofQueryPredData *pdata);

/** Return a printable string for a core data object.  Caller needs
 *  to g_free() the returned string.
 */
char * qof_query_core_to_string (char const *type, gpointer object,
			     QofAccessFunc fcn);

#endif /* QOF_QUERYCORE_H */