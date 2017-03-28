# $FreeBSD$

PORTNAME=	automater
PORTVERSION=	2.1
CATEGORIES=	security
MASTER_SITES=	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=        IP and URL analysis tool

LICENSE=	GPLv2

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests

USE_GITHUB=	yes
GH_ACCOUNT=	1aN0rmus
GH_PROJECT=	TekDefense-Automater
GH_TAGNAME= 	42548cf

USES=		python:2.7+  shebangfix
NO_BUILD=	yes

SHEBANG_FILES=	${WRKSRC}/Automater.py
FILELIST=	inputs.py outputs.py siteinfo.py  utilities.py

do-install:
#	${MKDIR} 	    	 ${STAGEDIR}${DOCSDIR}
#	${MKDIR} 	    	 ${STAGEDIR}${DATADIR}
	${MKDIR} 	     	 ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/automater
	${INSTALL_DATA} 	 ${FILELIST:S|^|${WRKSRC}/|} 		  ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/automater
	${INSTALL_DATA}		 ${FILELIST:S|^|${WRKSRC}/|} 		  ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/automater
#	${INSTALL_DATA}		 ${WRKSRC}/tekdefense.xml		  ${STAGEDIR}${DATADIR}
#	${INSTALL_DATA}		 ${WRKSRC}/sites.xml		  	  ${STAGEDIR}${DATADIR}
	${INSTALL_SCRIPT}	 ${WRKSRC}/Automater.py           	  ${STAGEDIR}${PREFIX}/bin/automater

.include <bsd.port.mk>
