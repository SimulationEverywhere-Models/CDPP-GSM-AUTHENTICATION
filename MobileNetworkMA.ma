[top]
components : AccessControl@AccessControl
components : MobileSwitchingCenter@MobileSwitchingCenter

in : MaxValidId 
in : Id
in : SRES_2

out : RAND
out : Ok

Link : MaxValidId MaxValidId@AccessControl
Link : Id Id@AccessControl
Link : SRES_2 SRES_2@MobileSwitchingCenter 
Link : RAND@AccessControl RAND
Link : Ok@MobileSwitchingCenter Ok 
Link : SRES_1@AccessControl SRES_1@MobileSwitchingCenter

[AccessControl]
distribution : normal
mean : 100
deviation : 100
