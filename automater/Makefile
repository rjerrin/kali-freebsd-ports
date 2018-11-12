# $FreeBSD$

PORTNAME=	automater
PORTVERSION=	0.21
CATEGORIES=	security

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	IP and URL analysis tool

LICENSE=	MIT

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests@${PY_FLAVOR}

USES=		python:2.7+  shebangfix

USE_GITHUB=	yes
GH_ACCOUNT=	1aN0rmus
GH_PROJECT=	TekDefense-Automater
GH_TAGNAME=	42548cf

NO_BUILD=	yes

SHEBANG_FILES=	${WRKSRC}/Automater.py
FILELIST=	inputs.py outputs.py siteinfo.py  utilities.py

OPTIONS_DEFINE=	DOCS

SUB_FILES=	__init__.py

do-install:

	${MKDIR} 	    	 ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/automater
	${MKDIR} 	     	 ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA}		 ${FILELIST:S|^|${WRKSRC}/|} 		  ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/automater
	${INSTALL_DATA} 	 ${WRKDIR}/__init__.py		          ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/automater/__init__.py
	${INSTALL_DATA}		 ${WRKSRC}/tekdefense.xml		  ${STAGEDIR}${ETCDIR}/tekdefense.xml.example
	${INSTALL_DATA}		 ${WRKSRC}/sites.xml		  	  ${STAGEDIR}${ETCDIR}/sites.xml.example
	${INSTALL_SCRIPT}	 ${WRKSRC}/Automater.py           	  ${STAGEDIR}${PREFIX}/bin/automater

post-install-DOCS-on:
	${MKDIR}	${STAGEDIR}${DOCSDIR}
	(cd ${WRKSRC}/docs	 && ${COPYTREE_SHARE} \* ${STAGEDIR}${DOCSDIR})

.include <bsd.port.mk>
