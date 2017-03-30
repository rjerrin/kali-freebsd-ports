# $FreeBSD$

PORTNAME=	dnsrecon
PORTVERSION=	0.8.9
DISTVERSIONPREFIX=	v
CATEGORIES=	dns
MASTER_SITES=	GH

MAINTAINER=	zackj901@yandex.com
COMMENT=	DNS enumeration tool

LICENSE=	GPLv3

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}dnspython>=0:${PORTSDIR}/dns/py-dnspython \
	  	${PYTHON_PKGNAMEPREFIX}netaddr>=0:${PORTSDIR}/net/py-netaddr \
		${PYTHON_PKGNAMEPREFIX}sqlite3>=0:${PORTSDIR}/databases/py-sqlite3

USE_GITHUB=	yes
GH_ACCOUNT=	darkoperator

USES=		tar:tgz python:2.7+  shebangfix
NO_BUILD=	yes

SHEBANG_FILES=	${WRKSRC}/dnsrecon.py
FILELIST=	namelist.txt subdomains-top1mil-20000.txt subdomains-top1mil-5000.txt subdomains-top1mil.txt

post-patch:
	  @${REINPLACE_CMD} -e 's|from lib|from dnsrecon|g' ${WRKSRC}/${PORTNAME}.py

do-install:
	${MKDIR} 	    	 ${STAGEDIR}${DOCSDIR}
	${MKDIR} 	    	 ${STAGEDIR}${DATADIR}
	${MKDIR} 	     	 ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/dnsrecon
	(cd ${WRKSRC}/lib && 	 ${COPYTREE_SHARE} \*			  ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/dnsrecon )
	${INSTALL_SCRIPT}	 ${WRKSRC}/dnsrecon.py           	  ${STAGEDIR}${PREFIX}/bin/dnsrecon
	${INSTALL_DATA}		 ${WRKSRC}/README.md			  ${STAGEDIR}${DOCSDIR}/README
	${INSTALL_DATA} 	 ${FILELIST:S|^|${WRKSRC}/|} 		  ${STAGEDIR}${DATADIR}

.include <bsd.port.mk>
