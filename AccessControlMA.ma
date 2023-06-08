%CDPlusPlus_Builder_Version_1.0.0

[top]
components : AccessControl@AccessControl 
out : Rand
out : SRES_1 
in : MaxValidId
in : Id 
Link : Id Id@AccessControl
Link : MaxValidId MaxValidId@AccessControl 
Link : Rand@AccessControl Rand
Link : SRES_1@AccessControl SRES_1

[AccessControl]
distribution : normal
mean : 100
deviation : 100
