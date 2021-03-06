/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeImageViewObject.h"
#include "TiEventContainerFactory.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/imageview>

NativeImageViewObject::NativeImageViewObject()
{
    imageView_ = NULL;
    left_ = 0;
    top_ = 0;
}

NativeImageViewObject::~NativeImageViewObject()
{
}

NativeImageViewObject* NativeImageViewObject::createImageView()
{
    return new NativeImageViewObject;
}

int NativeImageViewObject::getObjectType() const
{
    return N_TYPE_IMAGEVIEW;
}

int NativeImageViewObject::initialize(TiEventContainerFactory* containerFactory)
{
    imageView_ = bb::cascades::ImageView::create();
    setControl(imageView_);
    eventImageChanged_ = containerFactory->createEventContainer();
    eventImageChanged_->setDataProperty("type", "change");
    eventHandler_ = new ImageViewEventHandler(eventImageChanged_);
    return NATIVE_ERROR_OK;
}

int NativeImageViewObject::setImage(const char* image)
{
    // FIXME: following call fails to compile on R4
    //imageView_->setImage(bb::cascades::Image(image));
    return NATIVE_ERROR_OK;
}

void NativeImageViewObject::completeInitialization()
{
    NativeControlObject::completeInitialization();
    QObject::connect(imageView_, SIGNAL(imageChanged(const bb::cascades::Image)), eventHandler_, SLOT(imageChanged(const bb::cascades::Image)));
}

int NativeImageViewObject::setEventHandler(const char* eventName, TiEvent* event)
{
    if (strcmp(eventName, "change") == 0)
    {
        eventImageChanged_->addListener(event);
    }

    return NATIVE_ERROR_NOTSUPPORTED;
}
