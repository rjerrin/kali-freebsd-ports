# $FreeBSD$

PORTNAME=	acccheck
PORTVERSION=	0.2.1
CATEGORIES=	security
MASTER_SITES=	https://labs.portcullis.co.uk/download/
DISTFILES=	${DISTNAME:S/./-/g}${EXTRACT_SUFX}

MAINTAINER=	rihaz.jerrin@gmail.com
COMMENT=	Password dictionary attack tool for SMB

LICENSE=	GPLv2

RUN_DEPENDS=	smbclient:${PORTSDIR}/net/samba-smbclient

USES=	perl5 shebangfix
SHEBANG_FILES=	${WRKSRC}/acccheck.pl

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION:S/./-/g}

NO_BUILD=	yes
NO_ARCH=	yes

do-install:
	  ${INSTALL_SCRIPT}  	${WRKSRC}/acccheck.pl   	 ${STAGEDIR}${LOCALBASE}/bin/acccheck
	  ${MKDIR}  		${STAGEDIR}${DOCSDIR}
	  ${INSTALL_DATA}	${WRKSRC}/COPYING.ACCCHECK	 ${STAGEDIR}${DOCSDIR}
	  ${INSTALL_DATA}	${WRKSRC}/COPYING.GPL		 ${STAGEDIR}${DOCSDIR}
	  ${INSTALL_DATA}	${WRKSRC}/README.TXT	 	 ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
