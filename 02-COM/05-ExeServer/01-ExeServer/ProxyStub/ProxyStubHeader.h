

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for .\ProxyStub.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ProxyStubHeader_h__
#define __ProxyStubHeader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAddSubtract_FWD_DEFINED__
#define __IAddSubtract_FWD_DEFINED__
typedef interface IAddSubtract IAddSubtract;

#endif 	/* __IAddSubtract_FWD_DEFINED__ */


#ifndef __IMultiplyDevide_FWD_DEFINED__
#define __IMultiplyDevide_FWD_DEFINED__
typedef interface IMultiplyDevide IMultiplyDevide;

#endif 	/* __IMultiplyDevide_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAddSubtract_INTERFACE_DEFINED__
#define __IAddSubtract_INTERFACE_DEFINED__

/* interface IAddSubtract */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAddSubtract;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19EC9C50-0F01-4E1C-A67B-DA404E2DB19D")
    IAddSubtract : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SumOfTwoIntegers( 
            /* [in] */ int __MIDL__IAddSubtract0000,
            /* [in] */ int __MIDL__IAddSubtract0001,
            /* [out][in] */ int *__MIDL__IAddSubtract0002) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAddSubtractVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAddSubtract * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAddSubtract * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAddSubtract * This);
        
        HRESULT ( STDMETHODCALLTYPE *SumOfTwoIntegers )( 
            IAddSubtract * This,
            /* [in] */ int __MIDL__IAddSubtract0000,
            /* [in] */ int __MIDL__IAddSubtract0001,
            /* [out][in] */ int *__MIDL__IAddSubtract0002);
        
        END_INTERFACE
    } IAddSubtractVtbl;

    interface IAddSubtract
    {
        CONST_VTBL struct IAddSubtractVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAddSubtract_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAddSubtract_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAddSubtract_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAddSubtract_SumOfTwoIntegers(This,__MIDL__IAddSubtract0000,__MIDL__IAddSubtract0001,__MIDL__IAddSubtract0002)	\
    ( (This)->lpVtbl -> SumOfTwoIntegers(This,__MIDL__IAddSubtract0000,__MIDL__IAddSubtract0001,__MIDL__IAddSubtract0002) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAddSubtract_INTERFACE_DEFINED__ */


#ifndef __IMultiplyDevide_INTERFACE_DEFINED__
#define __IMultiplyDevide_INTERFACE_DEFINED__

/* interface IMultiplyDevide */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMultiplyDevide;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ED29EC5-9628-46E8-8285-4881CB5ECE63")
    IMultiplyDevide : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SubtractionOfTwoIntegers( 
            /* [in] */ int __MIDL__IMultiplyDevide0000,
            /* [in] */ int __MIDL__IMultiplyDevide0001,
            /* [out][in] */ int *__MIDL__IMultiplyDevide0002) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMultiplyDevideVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiplyDevide * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiplyDevide * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiplyDevide * This);
        
        HRESULT ( STDMETHODCALLTYPE *SubtractionOfTwoIntegers )( 
            IMultiplyDevide * This,
            /* [in] */ int __MIDL__IMultiplyDevide0000,
            /* [in] */ int __MIDL__IMultiplyDevide0001,
            /* [out][in] */ int *__MIDL__IMultiplyDevide0002);
        
        END_INTERFACE
    } IMultiplyDevideVtbl;

    interface IMultiplyDevide
    {
        CONST_VTBL struct IMultiplyDevideVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiplyDevide_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiplyDevide_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiplyDevide_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiplyDevide_SubtractionOfTwoIntegers(This,__MIDL__IMultiplyDevide0000,__MIDL__IMultiplyDevide0001,__MIDL__IMultiplyDevide0002)	\
    ( (This)->lpVtbl -> SubtractionOfTwoIntegers(This,__MIDL__IMultiplyDevide0000,__MIDL__IMultiplyDevide0001,__MIDL__IMultiplyDevide0002) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiplyDevide_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


