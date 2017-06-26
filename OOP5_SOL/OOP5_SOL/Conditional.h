#pragma once
#ifndef _CONDITIONAL_H
#define _CONDITIONAL_H

template<bool CONDITION,typename THEN,typename ELSE> struct IF;

template<typename THEN,typename ELSE> struct IF<true,THEN,ELSE> {
	typedef THEN CHECK;
};

template<typename THEN,typename ELSE> struct IF<false,THEN,ELSE> {
	typedef ELSE CHECK;
};



#endif