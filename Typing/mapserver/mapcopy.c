/******************************************************************************
 * $Id$
 *
 * Project: MapServer
 * Purpose: Functions to allow copying/cloning of maps
 * Author:  Sean Gillies, sgillies@frii.com
 *
 * Notes:
 * These functions are not in mapfile.c because that file is
 * cumbersome enough as it is.  There is agreement that this code and
 * that in mapfile.c should eventually be split up by object into
 * mapobj.c, layerobj.c, etc.  Or something like that.
 *
 * Unit tests are written in Python using PyUnit and are in
 * mapscript/python/tests/testCopyMap.py.  The tests can be
 * executed from the python directory as
 *
 *   python2 tests/testCopyMap.py
 *
 * I just find Python to be very handy for unit testing, that's all.
 *
 ******************************************************************************
 * Copyright (c) 1996-2005 Regents of the University of Minnesota.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies of this Software or works derived from this Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include <assert.h>
#include "mapserver.h"
#include "mapsymbol.h"

#include "mapcopy.h"

/***********************************************************************
 * msCopyProjectioExtended()                                           *
 *                                                                     *
 * Copy a projectionObj while adding additional arguments              *
 **********************************************************************/

int msCopyProjectionExtended(projectionObj *dst, projectionObj *src, char ** args, int num_args)
{

#ifdef USE_PROJ
  int i;

  MS_COPYSTELEM(numargs);
  MS_COPYSTELEM(gt);
  MS_COPYSTELEM(automatic);

  for (i = 0; i < dst->numargs; i++) {
    /* Our destination consists of unallocated pointers */
    dst->args[i] = msStrdup(src->args[i]);
  }
  for(i=0 ; i< num_args; i++) {
    dst->args[dst->numargs++] = msStrdup(args[i]);
  }
  if (dst->numargs != 0) {
    if (msProcessProjection(dst) != MS_SUCCESS)
      return MS_FAILURE;
  }
#endif
  MS_COPYSTELEM(wellknownprojection);
  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyProjection()                                                  *
 *                                                                     *
 * Copy a projectionObj                                                *
 **********************************************************************/

int msCopyProjection(projectionObj *dst, projectionObj *src)
{
  return msCopyProjectionExtended(dst,src,NULL,0);
}

/***********************************************************************
 * msCopyLine()                                                        *
 *                                                                     *
 * Copy a lineObj, using msCopyPoint()                                 *
 **********************************************************************/
int msCopyLine(lineObj *dst, lineObj *src)
{

  int i;

  dst->numpoints = src->numpoints;
  for (i = 0; i < dst->numpoints; i++) {
    MS_COPYPOINT(&(dst->point[i]), &(src->point[i]));
  }

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyShape()                                                       *
 *                                                                     *
 * Copy a shapeObj, using msCopyLine(), msCopyRect()                   *
 * Not completely implemented or tested.                               *
 **********************************************************************/
/*
int msCopyShapeObj(shapeObj *dst, shapeObj *src) {
  int i;
  copyProperty(&(dst->numlines), &(src->numlines), sizeof(int));
  for (i = 0; i < dst->numlines; i++) {
    msCopyLine(&(dst->line[i]), &(src->line[i]));
  }
  msCopyRect(&(dst->bounds), &(src->bounds));
  copyProperty(&(dst->type), &(src->type), sizeof(int));
  copyProperty(&(dst->index), &(src->index), sizeof(long));
  copyProperty(&(dst->tileindex), &(src->tileindex), sizeof(int));
  copyProperty(&(dst->classindex), &(src->classindex), sizeof(int));
  copyStringPropertyRealloc(&(dst->text), src->text);
  copyProperty(&(dst->numvalues), &(src->numvalues), sizeof(int));
  for (i = 0; i < dst->numvalues; i++) {
    copyStringPropertyRealloc(&(dst->values[i]), src->values[i]);
  }

  return(0);
}
*/

/**********************************************************************
 * msCopyItem()                                                        *
 *                                                                     *
 * Copy an itemObj                                                     *
 **********************************************************************/

int msCopyItem(itemObj *dst, itemObj *src)
{

  MS_COPYSTRING(dst->name, src->name);
  MS_COPYSTELEM(type);
  MS_COPYSTELEM(index);
  MS_COPYSTELEM(size);
  MS_COPYSTELEM(numdecimals);

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyHashTable()                                                   *
 *                                                                     *
 * Copy a hashTableObj, using msInsertHashTable()                      *
 **********************************************************************/

int msCopyHashTable(hashTableObj *dst, hashTableObj *src)
{
  const char *key=NULL;
  while (1) {
    key = msNextKeyFromHashTable(src, key);
    if (!key)
      break;
    else
      msInsertHashTable(dst, key, msLookupHashTable(src, key));
  }
  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyFontSet()                                                     *
 *                                                                     *
 * Copy a fontSetObj, using msCreateHashTable() and msCopyHashTable()  *
 **********************************************************************/

int msCopyFontSet(fontSetObj *dst, fontSetObj *src, mapObj *map)
{

  MS_COPYSTRING(dst->filename, src->filename);
  MS_COPYSTELEM(numfonts);
  if (&(src->fonts)) {
    /* if (!dst->fonts) */
    /* dst->fonts = msCreateHashTable(); */
    if (msCopyHashTable(&(dst->fonts), &(src->fonts)) != MS_SUCCESS)
      return MS_FAILURE;
  }

  dst->map = map;

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyExpression()                                                  *
 *                                                                     *
 * Copy an expressionObj, but only its string, type and flags          *
 **********************************************************************/

int msCopyExpression(expressionObj *dst, expressionObj *src)
{
  MS_COPYSTRING(dst->string, src->string);
  MS_COPYSTELEM(type);
  MS_COPYSTELEM(flags);
  dst->compiled = MS_FALSE;

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyJoin()                                                        *
 *                                                                     *
 * Copy a joinObj                                                      *
 **********************************************************************/

int msCopyJoin(joinObj *dst, joinObj *src)
{
  MS_COPYSTRING(dst->name, src->name);

  /* makes no sense to copy the items or values
     since they are runtime additions to the mapfile */

  MS_COPYSTRING(dst->table, src->table);
  MS_COPYSTRING(dst->from, src->from);
  MS_COPYSTRING(dst->to, src->to);
  MS_COPYSTRING(dst->header, src->header);
#ifndef __cplusplus
  MS_COPYSTRING(dst->template, src->template);
#else
  MS_COPYSTRING(dst->_template, src->_template);
#endif
  MS_COPYSTRING(dst->footer, src->footer);
  dst->type = src->type;
  MS_COPYSTRING(dst->connection, src->connection);

  MS_COPYSTELEM(connectiontype);

  /* TODO: need to handle joininfo (probably should be just set to NULL) */
  dst->joininfo = NULL;

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyQueryMap()                                                    *
 *                                                                     *
 * Copy a queryMapObj, using msCopyColor()                             *
 **********************************************************************/

int msCopyQueryMap(queryMapObj *dst, queryMapObj *src)
{
  MS_COPYSTELEM(height);
  MS_COPYSTELEM(width);
  MS_COPYSTELEM(status);
  MS_COPYSTELEM(style);
  MS_COPYCOLOR(&(dst->color), &(src->color));

  return MS_SUCCESS;
}


/***********************************************************************
 * msCopyLeader()                                                      *
 *                                                                     *
 * Copy a labelLeaderObj, using msCopyStyle()                          *
 **********************************************************************/

int msCopyLabelLeader(labelLeaderObj *dst, labelLeaderObj *src)
{
  int i;
  assert(dst && src);
  MS_COPYSTELEM(gridstep);
  MS_COPYSTELEM(maxdistance);
  /*
   ** now the styles
   */

  /* free any previous styles on the dst label */
  for(i=0; i<dst->numstyles; i++) { /* each style */
    if (dst->styles[i]!=NULL) {
      if( freeStyle(dst->styles[i]) == MS_SUCCESS ) msFree(dst->styles[i]);
    }
  }
  dst->numstyles = 0;

  for (i = 0; i < src->numstyles; i++) {
    if (msGrowLeaderStyles(dst) == NULL)
      return MS_FAILURE;
    if (initStyle(dst->styles[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to init style.", "msCopyLabel()");
      return MS_FAILURE;
    }
    if (msCopyStyle(dst->styles[i], src->styles[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to copy style.", "msCopyLabel()");
      return MS_FAILURE;
    }
    dst->numstyles++;
  }
  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyLabel()                                                       *
 *                                                                     *
 * Copy a labelObj, using msCopyColor() and msCopyStyle()              *
 **********************************************************************/

int msCopyLabel(labelObj *dst, labelObj *src)
{
  int i;

  for(i=0; i<MS_LABEL_BINDING_LENGTH; i++) {
    MS_COPYSTRING(dst->bindings[i].item, src->bindings[i].item);
    dst->bindings[i].index = src->bindings[i].index; /* no way to use the macros */
  }
  MS_COPYSTELEM(numbindings);

  MS_COPYSTRING(dst->font, src->font);

  MS_COPYCOLOR(&(dst->color), &(src->color));
  MS_COPYCOLOR(&(dst->outlinecolor), &(src->outlinecolor));
  MS_COPYCOLOR(&(dst->shadowcolor), &(src->shadowcolor));

  MS_COPYSTELEM(shadowsizex);
  MS_COPYSTELEM(shadowsizey);

  MS_COPYSTELEM(size);
  MS_COPYSTELEM(minsize);
  MS_COPYSTELEM(maxsize);
  MS_COPYSTELEM(position);
  MS_COPYSTELEM(offsetx);
  MS_COPYSTELEM(offsety);
  MS_COPYSTELEM(angle);
  MS_COPYSTELEM(anglemode);
  MS_COPYSTELEM(buffer);
  MS_COPYSTELEM(wrap);
  MS_COPYSTELEM(align);
  MS_COPYSTELEM(maxlength);
  MS_COPYSTELEM(minfeaturesize);

  MS_COPYSTELEM(minscaledenom);
  MS_COPYSTELEM(maxscaledenom);

  MS_COPYSTELEM(autominfeaturesize);

  MS_COPYSTELEM(mindistance);
  MS_COPYSTELEM(partials);
  MS_COPYSTELEM(force);
  MS_COPYSTELEM(priority);

  MS_COPYSTELEM(repeatdistance);
  MS_COPYSTELEM(maxoverlapangle);


  MS_COPYSTRING(dst->encoding, src->encoding);

  MS_COPYSTELEM(outlinewidth);
  MS_COPYSTELEM(space_size_10);

  if (msCopyExpression(&(dst->expression), &(src->expression)) != MS_SUCCESS) {
    msSetError(MS_MEMERR, "Failed to copy expression.", "msCopyLabel()");
    return MS_FAILURE;
  }

  if (msCopyExpression(&(dst->text), &(src->text)) != MS_SUCCESS) {
    msSetError(MS_MEMERR, "Failed to copy text.", "msCopyLabel()");
    return MS_FAILURE;
  }

  /*
  ** now the styles
  */

  /* free any previous styles on the dst label */
  for(i=0; i<dst->numstyles; i++) { /* each style */
    if (dst->styles[i]!=NULL) {
      if( freeStyle(dst->styles[i]) == MS_SUCCESS ) msFree(dst->styles[i]);
    }
  }
  dst->numstyles = 0;

  for (i = 0; i < src->numstyles; i++) {
    if (msGrowLabelStyles(dst) == NULL)
      return MS_FAILURE;
    if (initStyle(dst->styles[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to init style.", "msCopyLabel()");
      return MS_FAILURE;
    }
    if (msCopyStyle(dst->styles[i], src->styles[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to copy style.", "msCopyLabel()");
      return MS_FAILURE;
    }
    dst->numstyles++;
  }

  if(src->leader) {
    dst->leader = msSmallMalloc(sizeof(labelLeaderObj));
    initLeader(dst->leader);
    msCopyLabelLeader(dst->leader,src->leader);
  } else {
    if(dst->leader) {
      freeLabelLeader(dst->leader);
      msFree(dst->leader);
    }
    dst->leader = NULL;
  }

  return MS_SUCCESS;


/***********************************************************************
 * msCopyWeb()                                                         *
 *                                                                     *
 * Copy webObj, using msCopyRect(), msCreateHashTable(), and           *
 * msCopyHashTable()                                                   *
 **********************************************************************/

int msCopyWeb(webObj *dst, webObj *src, mapObj *map)
{

  MS_COPYSTRING(dst->log, src->log);
  MS_COPYSTRING(dst->imagepath, src->imagepath);
  MS_COPYSTRING(dst->imageurl, src->imageurl);
  dst->map = map;
#ifndef __cplusplus
  MS_COPYSTRING(dst->template, src->template);
#else
  MS_COPYSTRING(dst->_template, src->_template);
#endif
  MS_COPYSTRING(dst->header, src->header);
  MS_COPYSTRING(dst->footer, src->footer);
  MS_COPYSTRING(dst->empty, src->empty);
  MS_COPYSTRING(dst->error, src->error);

  MS_COPYRECT(&(dst->extent), &(src->extent));

  MS_COPYSTELEM(minscaledenom);
  MS_COPYSTELEM(maxscaledenom);
  MS_COPYSTRING(dst->mintemplate, src->mintemplate);
  MS_COPYSTRING(dst->maxtemplate, src->maxtemplate);

  if (&(src->metadata)) {
    /* dst->metadata = msCreateHashTable(); */
    if (msCopyHashTable(&(dst->metadata), &(src->metadata)) != MS_SUCCESS)
      return MS_FAILURE;
  }
  msCopyHashTable(&dst->validation,&src->validation);

  MS_COPYSTRING(dst->queryformat, src->queryformat);
  MS_COPYSTRING(dst->legendformat, src->legendformat);
  MS_COPYSTRING(dst->browseformat, src->browseformat);

  return MS_SUCCESS ;
}

/***********************************************************************
 * msCopyStyle()                                                       *
 *                                                                     *
 * Copy a styleObj, using msCopyColor()                                *
 **********************************************************************/

int msCopyStyle(styleObj *dst, styleObj *src)
{
  int i;

  for(i=0; i<MS_STYLE_BINDING_LENGTH; i++) {
    MS_COPYSTRING(dst->bindings[i].item, src->bindings[i].item);
    dst->bindings[i].index = src->bindings[i].index; /* no way to use the macros */
  }
  MS_COPYSTELEM(numbindings);

  MS_COPYCOLOR(&(dst->color), &(src->color));
  MS_COPYCOLOR(&(dst->outlinecolor),&(src->outlinecolor));
  MS_COPYCOLOR(&(dst->backgroundcolor), &(src->backgroundcolor));

  MS_COPYCOLOR(&(dst->mincolor), &(src->mincolor));
  MS_COPYCOLOR(&(dst->maxcolor), &(src->maxcolor));

  MS_COPYSTRING(dst->symbolname, src->symbolname);
  MS_COPYSTELEM(patternlength);
  for(i=0; i<src->patternlength; i++)
    dst->pattern[i]=src->pattern[i];
  MS_COPYSTELEM(initialgap);
  MS_COPYSTELEM(gap);
  MS_COPYSTELEM(linejoin);
  MS_COPYSTELEM(linejoinmaxsize);
  MS_COPYSTELEM(linecap);
  MS_COPYSTELEM(symbol);
  MS_COPYSTELEM(size);
  MS_COPYSTELEM(minsize);
  MS_COPYSTELEM(maxsize);
  MS_COPYSTELEM(width);
  MS_COPYSTELEM(minwidth);
  MS_COPYSTELEM(maxwidth);
  MS_COPYSTELEM(offsetx);
  MS_COPYSTELEM(offsety);
  MS_COPYSTELEM(angle);
  MS_COPYSTELEM(minvalue);
  MS_COPYSTELEM(maxvalue);
  MS_COPYSTELEM(opacity);
  MS_COPYSTRING(dst->_geomtransform.string, src->_geomtransform.string);
  MS_COPYSTELEM(_geomtransform.type);
  MS_COPYSTRING(dst->rangeitem, src->rangeitem);
  MS_COPYSTELEM(rangeitemindex);
  MS_COPYSTELEM(outlinewidth);
  MS_COPYSTELEM(minscaledenom);
  MS_COPYSTELEM(maxscaledenom);
  /* TODO: add copy for bindings */

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyClass()                                                       *
 *                                                                     *
 * Copy a classObj, using msCopyExpression(), msCopyStyle(),           *
 * msCopyLabel(), msCreateHashTable(), msCopyHashTable()               *
 **********************************************************************/

int msCopyClass(classObj *dst, classObj *src, layerObj *layer)
{
  int i, return_value;

  return_value = msCopyExpression(&(dst->expression),&(src->expression));
  if (return_value != MS_SUCCESS) {
    msSetError(MS_MEMERR, "Failed to copy expression.", "msCopyClass()");
    return MS_FAILURE;
  }

  MS_COPYSTELEM(status);

  /* free any previous styles on the dst layer */
  for(i=0; i<dst->numstyles; i++) { /* each style */
    if (dst->styles[i]!=NULL) {
      if( freeStyle(dst->styles[i]) == MS_SUCCESS ) {
        msFree(dst->styles[i]);
      }
    }
  }
  dst->numstyles = 0;

  for (i = 0; i < src->numstyles; i++) {
    if (msGrowClassStyles(dst) == NULL)
      return MS_FAILURE;
    if (initStyle(dst->styles[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to init style.", "msCopyClass()");
      return MS_FAILURE;
    }
    if (msCopyStyle(dst->styles[i], src->styles[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to copy style.", "msCopyClass()");
      return MS_FAILURE;
    }

    dst->numstyles++;
  }

  for (i=0; i<src->numlabels; i++) {
    if (msGrowClassLabels(dst) == NULL)
      return MS_FAILURE;
    initLabel(dst->labels[i]);
    if (msCopyLabel(dst->labels[i], src->labels[i]) != MS_SUCCESS) {
      msSetError(MS_MEMERR, "Failed to copy label.", "msCopyClass()");
      return MS_FAILURE;
    }

    dst->numlabels++;
  }
  MS_COPYSTELEM(numlabels);

  if(src->leader) {
    if(dst->leader) {
      freeLabelLeader(dst->leader);
    }
    if(!dst->leader) {
      dst->leader = msSmallMalloc(sizeof(labelLeaderObj));
      initLeader(dst->leader);
    }
    msCopyLabelLeader(dst->leader,src->leader);
  }

  MS_COPYSTRING(dst->keyimage, src->keyimage);
  MS_COPYSTRING(dst->name, src->name);
  MS_COPYSTRING(dst->title, src->title);
  MS_COPYSTRING(dst->group, src->group);

  if (msCopyExpression(&(dst->text), &(src->text)) != MS_SUCCESS) {
    msSetError(MS_MEMERR, "Failed to copy text.", "msCopyClass()");
    return MS_FAILURE;
  }

#ifndef __cplusplus
  MS_COPYSTRING(dst->template, src->template);
#else
  MS_COPYSTRING(dst->_template, src->_template);
#endif

  if (&(src->metadata) != NULL) {
    /* dst->metadata = msCreateHashTable(); */
    msCopyHashTable(&(dst->metadata), &(src->metadata));
  }
  msCopyHashTable(&dst->validation,&src->validation);

  MS_COPYSTELEM(minscaledenom);
  MS_COPYSTELEM(maxscaledenom);
  MS_COPYSTELEM(layer);
  MS_COPYSTELEM(debug);

  return MS_SUCCESS;
}

int msCopyCluster(clusterObj *dst, clusterObj *src)
{
  int return_value;

  MS_COPYSTELEM(maxdistance);
  MS_COPYSTELEM(buffer);
  MS_COPYSTRING(dst->region, src->region);

  return_value = msCopyExpression(&(dst->group),&(src->group));
  if (return_value != MS_SUCCESS) {
    msSetError(MS_MEMERR, "Failed to copy cluster group.", "msCopyCluster()");
    return MS_FAILURE;
  }

  return_value = msCopyExpression(&(dst->filter),&(src->filter));
  if (return_value != MS_SUCCESS) {
    msSetError(MS_MEMERR, "Failed to copy cluster filter.", "msCopyCluster()");
    return MS_FAILURE;
  }

  return MS_SUCCESS;
}

/***********************************************************************
 * msCopyGrid()                                                        *
 **********************************************************************/
}
}

}
