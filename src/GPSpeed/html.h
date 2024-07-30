// vim: set ft=html:
const char HTML[] PROGMEM = R"=====(
<!doctype html>
<html>
  <head>
    <title>CG balancer</title>

    <style>
/*------------------   W3 CSS  --------------------------------------------*/
/* W3PRO.CSS 4.15 December 2020 by Jan Egil and Borge Refsnes */
html{box-sizing:border-box}*,*:before,*:after{box-sizing:inherit}
/* Extract from normalize.css by Nicolas Gallagher and Jonathan Neal git.io/normalize */
html{-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}
article,aside,details,figcaption,figure,footer,header,main,menu,nav,section{display:block}summary{display:list-item}
audio,canvas,progress,video{display:inline-block}progress{vertical-align:baseline}
audio:not([controls]){display:none;height:0}[hidden],template{display:none}
a{background-color:transparent}a:active,a:hover{outline-width:0}
abbr[title]{border-bottom:none;text-decoration:underline;text-decoration:underline dotted}
b,strong{font-weight:bolder}dfn{font-style:italic}mark{background:#ff0;color:#000}
small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}
sub{bottom:-0.25em}sup{top:-0.5em}figure{margin:1em 40px}img{border-style:none}
code,kbd,pre,samp{font-family:monospace,monospace;font-size:1em}hr{box-sizing:content-box;height:0;overflow:visible}
button,input,select,textarea,optgroup{font:inherit;margin:0}optgroup{font-weight:bold}
button,input{overflow:visible}button,select{text-transform:none}
button,[type=button],[type=reset],[type=submit]{-webkit-appearance:button}
button::-moz-focus-inner,[type=button]::-moz-focus-inner,[type=reset]::-moz-focus-inner,[type=submit]::-moz-focus-inner{border-style:none;padding:0}
button:-moz-focusring,[type=button]:-moz-focusring,[type=reset]:-moz-focusring,[type=submit]:-moz-focusring{outline:1px dotted ButtonText}
fieldset{border:1px solid #c0c0c0;margin:0 2px;padding:.35em .625em .75em}
legend{color:inherit;display:table;max-width:100%;padding:0;white-space:normal}textarea{overflow:auto}
[type=checkbox],[type=radio]{padding:0}
[type=number]::-webkit-inner-spin-button,[type=number]::-webkit-outer-spin-button{height:auto}
[type=search]{-webkit-appearance:textfield;outline-offset:-2px}
[type=search]::-webkit-search-decoration{-webkit-appearance:none}
::-webkit-file-upload-button{-webkit-appearance:button;font:inherit}
/* End extract */
html,body{font-family:Verdana,sans-serif;font-size:15px;line-height:1.5}html{overflow-x:hidden}
h1{font-size:36px}h2{font-size:30px}h3{font-size:24px}h4{font-size:20px}h5{font-size:18px}h6{font-size:16px}
.w3-serif{font-family:serif}.w3-sans-serif{font-family:sans-serif}.w3-cursive{font-family:cursive}.w3-monospace{font-family:monospace}
h1,h2,h3,h4,h5,h6{font-family:"Segoe UI",Arial,sans-serif;font-weight:400;margin:10px 0}.w3-wide{letter-spacing:4px}
hr{border:0;border-top:1px solid #eee;margin:20px 0}
.w3-image{max-width:100%;height:auto}img{vertical-align:middle}a{color:inherit}
.w3-table,.w3-table-all{border-collapse:collapse;border-spacing:0;width:100%;display:table}.w3-table-all{border:1px solid #ccc}
.w3-bordered tr,.w3-table-all tr{border-bottom:1px solid #ddd}.w3-striped tbody tr:nth-child(even){background-color:#f1f1f1}
.w3-table-all tr:nth-child(odd){background-color:#fff}.w3-table-all tr:nth-child(even){background-color:#f1f1f1}
.w3-hoverable tbody tr:hover,.w3-ul.w3-hoverable li:hover{background-color:#ccc}.w3-centered tr th,.w3-centered tr td{text-align:center}
.w3-table td,.w3-table th,.w3-table-all td,.w3-table-all th{padding:8px 8px;display:table-cell;text-align:left;vertical-align:top}
.w3-table th:first-child,.w3-table td:first-child,.w3-table-all th:first-child,.w3-table-all td:first-child{padding-left:16px}
.w3-btn,.w3-button{border:none;display:inline-block;padding:8px 16px;vertical-align:middle;overflow:hidden;text-decoration:none;color:inherit;background-color:inherit;text-align:center;cursor:pointer;white-space:nowrap}
.w3-btn:hover{box-shadow:0 8px 16px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19)}
.w3-btn,.w3-button{-webkit-touch-callout:none;-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}   
.w3-disabled,.w3-btn:disabled,.w3-button:disabled{cursor:not-allowed;opacity:0.3}.w3-disabled *,:disabled *{pointer-events:none}
.w3-btn.w3-disabled:hover,.w3-btn:disabled:hover{box-shadow:none}
.w3-badge,.w3-tag{background-color:#000;color:#fff;display:inline-block;padding-left:8px;padding-right:8px;text-align:center}.w3-badge{border-radius:50%}
.w3-ul{list-style-type:none;padding:0;margin:0}.w3-ul li{padding:8px 16px;border-bottom:1px solid #ddd}.w3-ul li:last-child{border-bottom:none}
.w3-tooltip,.w3-display-container{position:relative}.w3-tooltip .w3-text{display:none}.w3-tooltip:hover .w3-text{display:inline-block}
.w3-ripple:active{opacity:0.5}.w3-ripple{transition:opacity 0s}
.w3-input{padding:8px;display:block;border:none;border-bottom:1px solid #ccc;width:100%}
.w3-select{padding:9px 0;width:100%;border:none;border-bottom:1px solid #ccc}
.w3-dropdown-click,.w3-dropdown-hover{position:relative;display:inline-block;cursor:pointer}
.w3-dropdown-hover:hover .w3-dropdown-content{display:block}
.w3-dropdown-hover:first-child,.w3-dropdown-click:hover{background-color:#ccc;color:#000}
.w3-dropdown-hover:hover > .w3-button:first-child,.w3-dropdown-click:hover > .w3-button:first-child{background-color:#ccc;color:#000}
.w3-dropdown-content{cursor:auto;color:#000;background-color:#fff;display:none;position:absolute;min-width:160px;margin:0;padding:0;z-index:1}
.w3-check,.w3-radio{width:24px;height:24px;position:relative;top:6px}
.w3-sidebar{height:100%;width:200px;background-color:#fff;position:fixed!important;z-index:1;overflow:auto}
.w3-bar-block .w3-dropdown-hover,.w3-bar-block .w3-dropdown-click{width:100%}
.w3-bar-block .w3-dropdown-hover .w3-dropdown-content,.w3-bar-block .w3-dropdown-click .w3-dropdown-content{min-width:100%}
.w3-bar-block .w3-dropdown-hover .w3-button,.w3-bar-block .w3-dropdown-click .w3-button{width:100%;text-align:left;padding:8px 16px}
.w3-main,#main{transition:margin-left .4s}
.w3-modal{z-index:3;display:none;padding-top:100px;position:fixed;left:0;top:0;width:100%;height:100%;overflow:auto;background-color:rgb(0,0,0);background-color:rgba(0,0,0,0.4)}
.w3-modal-content{margin:auto;background-color:#fff;position:relative;padding:0;outline:0;width:600px}
.w3-bar{width:100%;overflow:hidden}.w3-center .w3-bar{display:inline-block;width:auto}
.w3-bar .w3-bar-item{padding:8px 16px;float:left;width:auto;border:none;display:block;outline:0}
.w3-bar .w3-dropdown-hover,.w3-bar .w3-dropdown-click{position:static;float:left}
.w3-bar .w3-button{white-space:normal}
.w3-bar-block .w3-bar-item{width:100%;display:block;padding:8px 16px;text-align:left;border:none;white-space:normal;float:none;outline:0}
.w3-bar-block.w3-center .w3-bar-item{text-align:center}.w3-block{display:block;width:100%}
.w3-responsive{display:block;overflow-x:auto}
.w3-container:after,.w3-container:before,.w3-panel:after,.w3-panel:before,.w3-row:after,.w3-row:before,.w3-row-padding:after,.w3-row-padding:before,
.w3-cell-row:before,.w3-cell-row:after,.w3-clear:after,.w3-clear:before,.w3-bar:before,.w3-bar:after{content:"";display:table;clear:both}
.w3-col,.w3-half,.w3-third,.w3-twothird,.w3-threequarter,.w3-quarter{float:left;width:100%}
.w3-col.s1{width:8.33333%}.w3-col.s2{width:16.66666%}.w3-col.s3{width:24.99999%}.w3-col.s4{width:33.33333%}
.w3-col.s5{width:41.66666%}.w3-col.s6{width:49.99999%}.w3-col.s7{width:58.33333%}.w3-col.s8{width:66.66666%}
.w3-col.s9{width:74.99999%}.w3-col.s10{width:83.33333%}.w3-col.s11{width:91.66666%}.w3-col.s12{width:99.99999%}
@media (min-width:601px){.w3-col.m1{width:8.33333%}.w3-col.m2{width:16.66666%}.w3-col.m3,.w3-quarter{width:24.99999%}.w3-col.m4,.w3-third{width:33.33333%}
.w3-col.m5{width:41.66666%}.w3-col.m6,.w3-half{width:49.99999%}.w3-col.m7{width:58.33333%}.w3-col.m8,.w3-twothird{width:66.66666%}
.w3-col.m9,.w3-threequarter{width:74.99999%}.w3-col.m10{width:83.33333%}.w3-col.m11{width:91.66666%}.w3-col.m12{width:99.99999%}}
@media (min-width:993px){.w3-col.l1{width:8.33333%}.w3-col.l2{width:16.66666%}.w3-col.l3{width:24.99999%}.w3-col.l4{width:33.33333%}
.w3-col.l5{width:41.66666%}.w3-col.l6{width:49.99999%}.w3-col.l7{width:58.33333%}.w3-col.l8{width:66.66666%}
.w3-col.l9{width:74.99999%}.w3-col.l10{width:83.33333%}.w3-col.l11{width:91.66666%}.w3-col.l12{width:99.99999%}}
.w3-rest{overflow:hidden}.w3-stretch{margin-left:-16px;margin-right:-16px}
.w3-content,.w3-auto{margin-left:auto;margin-right:auto}.w3-content{max-width:980px}.w3-auto{max-width:1140px}
.w3-cell-row{display:table;width:100%}.w3-cell{display:table-cell}
.w3-cell-top{vertical-align:top}.w3-cell-middle{vertical-align:middle}.w3-cell-bottom{vertical-align:bottom}
.w3-hide{display:none!important}.w3-show-block,.w3-show{display:block!important}.w3-show-inline-block{display:inline-block!important}
@media (max-width:1205px){.w3-auto{max-width:95%}}
@media (max-width:600px){.w3-modal-content{margin:0 10px;width:auto!important}.w3-modal{padding-top:30px}
.w3-dropdown-hover.w3-mobile .w3-dropdown-content,.w3-dropdown-click.w3-mobile .w3-dropdown-content{position:relative}	
.w3-hide-small{display:none!important}.w3-mobile{display:block;width:100%!important}.w3-bar-item.w3-mobile,.w3-dropdown-hover.w3-mobile,.w3-dropdown-click.w3-mobile{text-align:center}
.w3-dropdown-hover.w3-mobile,.w3-dropdown-hover.w3-mobile .w3-btn,.w3-dropdown-hover.w3-mobile .w3-button,.w3-dropdown-click.w3-mobile,.w3-dropdown-click.w3-mobile .w3-btn,.w3-dropdown-click.w3-mobile .w3-button{width:100%}}
@media (max-width:768px){.w3-modal-content{width:500px}.w3-modal{padding-top:50px}}
@media (min-width:993px){.w3-modal-content{width:900px}.w3-hide-large{display:none!important}.w3-sidebar.w3-collapse{display:block!important}}
@media (max-width:992px) and (min-width:601px){.w3-hide-medium{display:none!important}}
@media (max-width:992px){.w3-sidebar.w3-collapse{display:none}.w3-main{margin-left:0!important;margin-right:0!important}.w3-auto{max-width:100%}}
.w3-top,.w3-bottom{position:fixed;width:100%;z-index:1}.w3-top{top:0}.w3-bottom{bottom:0}
.w3-overlay{position:fixed;display:none;width:100%;height:100%;top:0;left:0;right:0;bottom:0;background-color:rgba(0,0,0,0.5);z-index:2}
.w3-display-topleft{position:absolute;left:0;top:0}.w3-display-topright{position:absolute;right:0;top:0}
.w3-display-bottomleft{position:absolute;left:0;bottom:0}.w3-display-bottomright{position:absolute;right:0;bottom:0}
.w3-display-middle{position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);-ms-transform:translate(-50%,-50%)}
.w3-display-left{position:absolute;top:50%;left:0%;transform:translate(0%,-50%);-ms-transform:translate(-0%,-50%)}
.w3-display-right{position:absolute;top:50%;right:0%;transform:translate(0%,-50%);-ms-transform:translate(0%,-50%)}
.w3-display-topmiddle{position:absolute;left:50%;top:0;transform:translate(-50%,0%);-ms-transform:translate(-50%,0%)}
.w3-display-bottommiddle{position:absolute;left:50%;bottom:0;transform:translate(-50%,0%);-ms-transform:translate(-50%,0%)}
.w3-display-container:hover .w3-display-hover{display:block}.w3-display-container:hover span.w3-display-hover{display:inline-block}.w3-display-hover{display:none}
.w3-display-position{position:absolute}
.w3-circle{border-radius:50%}
.w3-round-small{border-radius:2px}.w3-round,.w3-round-medium{border-radius:4px}.w3-round-large{border-radius:8px}.w3-round-xlarge{border-radius:16px}.w3-round-xxlarge{border-radius:32px}
.w3-row-padding,.w3-row-padding>.w3-half,.w3-row-padding>.w3-third,.w3-row-padding>.w3-twothird,.w3-row-padding>.w3-threequarter,.w3-row-padding>.w3-quarter,.w3-row-padding>.w3-col{padding:0 8px}
.w3-container,.w3-panel{padding:0.01em 16px}.w3-panel{margin-top:16px;margin-bottom:16px}
.w3-code,.w3-codespan{font-family:Consolas,"courier new";font-size:16px}
.w3-code{width:auto;background-color:#fff;padding:8px 12px;border-left:4px solid #4CAF50;word-wrap:break-word}
.w3-codespan{color:crimson;background-color:#f1f1f1;padding-left:4px;padding-right:4px;font-size:110%}
.w3-card,.w3-card-2{box-shadow:0 2px 5px 0 rgba(0,0,0,0.16),0 2px 10px 0 rgba(0,0,0,0.12)}
.w3-card-4,.w3-hover-shadow:hover{box-shadow:0 4px 10px 0 rgba(0,0,0,0.2),0 4px 20px 0 rgba(0,0,0,0.19)}
.w3-spin{animation:w3-spin 2s infinite linear}@keyframes w3-spin{0%{transform:rotate(0deg)}100%{transform:rotate(359deg)}}
.w3-animate-fading{animation:fading 10s infinite}@keyframes fading{0%{opacity:0}50%{opacity:1}100%{opacity:0}}
.w3-animate-opacity{animation:opac 0.8s}@keyframes opac{from{opacity:0} to{opacity:1}}
.w3-animate-top{position:relative;animation:animatetop 0.4s}@keyframes animatetop{from{top:-300px;opacity:0} to{top:0;opacity:1}}
.w3-animate-left{position:relative;animation:animateleft 0.4s}@keyframes animateleft{from{left:-300px;opacity:0} to{left:0;opacity:1}}
.w3-animate-right{position:relative;animation:animateright 0.4s}@keyframes animateright{from{right:-300px;opacity:0} to{right:0;opacity:1}}
.w3-animate-bottom{position:relative;animation:animatebottom 0.4s}@keyframes animatebottom{from{bottom:-300px;opacity:0} to{bottom:0;opacity:1}}
.w3-animate-zoom {animation:animatezoom 0.6s}@keyframes animatezoom{from{transform:scale(0)} to{transform:scale(1)}}
.w3-animate-input{transition:width 0.4s ease-in-out}.w3-animate-input:focus{width:100%!important}
.w3-opacity,.w3-hover-opacity:hover{opacity:0.60}.w3-opacity-off,.w3-hover-opacity-off:hover{opacity:1}
.w3-opacity-max{opacity:0.25}.w3-opacity-min{opacity:0.75}
.w3-greyscale-max,.w3-grayscale-max,.w3-hover-greyscale:hover,.w3-hover-grayscale:hover{filter:grayscale(100%)}
.w3-greyscale,.w3-grayscale{filter:grayscale(75%)}.w3-greyscale-min,.w3-grayscale-min{filter:grayscale(50%)}
.w3-sepia{filter:sepia(75%)}.w3-sepia-max,.w3-hover-sepia:hover{filter:sepia(100%)}.w3-sepia-min{filter:sepia(50%)}
.w3-tiny{font-size:10px!important}.w3-small{font-size:12px!important}.w3-medium{font-size:15px!important}.w3-large{font-size:18px!important}
.w3-xlarge{font-size:24px!important}.w3-xxlarge{font-size:36px!important}.w3-xxxlarge{font-size:48px!important}.w3-jumbo{font-size:64px!important}
.w3-left-align{text-align:left!important}.w3-right-align{text-align:right!important}.w3-justify{text-align:justify!important}.w3-center{text-align:center!important}
.w3-border-0{border:0!important}.w3-border{border:1px solid #ccc!important}
.w3-border-top{border-top:1px solid #ccc!important}.w3-border-bottom{border-bottom:1px solid #ccc!important}
.w3-border-left{border-left:1px solid #ccc!important}.w3-border-right{border-right:1px solid #ccc!important}
.w3-topbar{border-top:6px solid #ccc!important}.w3-bottombar{border-bottom:6px solid #ccc!important}
.w3-leftbar{border-left:6px solid #ccc!important}.w3-rightbar{border-right:6px solid #ccc!important}
.w3-section,.w3-code{margin-top:16px!important;margin-bottom:16px!important}
.w3-margin{margin:16px!important}.w3-margin-top{margin-top:16px!important}.w3-margin-bottom{margin-bottom:16px!important}
.w3-margin-left{margin-left:16px!important}.w3-margin-right{margin-right:16px!important}
.w3-padding-small{padding:4px 8px!important}.w3-padding{padding:8px 16px!important}.w3-padding-large{padding:12px 24px!important}
.w3-padding-16{padding-top:16px!important;padding-bottom:16px!important}.w3-padding-24{padding-top:24px!important;padding-bottom:24px!important}
.w3-padding-32{padding-top:32px!important;padding-bottom:32px!important}.w3-padding-48{padding-top:48px!important;padding-bottom:48px!important}
.w3-padding-64{padding-top:64px!important;padding-bottom:64px!important}
.w3-padding-top-64{padding-top:64px!important}.w3-padding-top-48{padding-top:48px!important}
.w3-padding-top-32{padding-top:32px!important}.w3-padding-top-24{padding-top:24px!important}
.w3-left{float:left!important}.w3-right{float:right!important}
.w3-button:hover{color:#000!important;background-color:#ccc!important}
.w3-transparent,.w3-hover-none:hover{background-color:transparent!important}
/*------------------   W3 Color theme --------------------------------------------*/
.w3-theme-l5 {color:#000 !important; background-color:#faf0fc !important}
.w3-theme-l4 {color:#000 !important; background-color:#efcef4 !important}
.w3-theme-l3 {color:#000 !important; background-color:#de9eea !important}
.w3-theme-l2 {color:#fff !important; background-color:#ce6ddf !important}
.w3-theme-l1 {color:#fff !important; background-color:#be3dd4 !important}
.w3-theme-d1 {color:#fff !important; background-color:#8c239e !important}
.w3-theme-d2 {color:#fff !important; background-color:#7c1f8d !important}
.w3-theme-d3 {color:#fff !important; background-color:#6d1b7b !important}
.w3-theme-d4 {color:#fff !important; background-color:#5d1769 !important}
.w3-theme-d5 {color:#fff !important; background-color:#4e1358 !important}

.w3-theme-light {color:#000 !important; background-color:#faf0fc !important}
.w3-theme-dark {color:#fff !important; background-color:#4e1358 !important}
.w3-theme-action {color:#fff !important; background-color:#4e1358 !important}

.w3-theme {color:#fff !important; background-color:#9c27b0 !important}
.w3-text-theme {color:#9c27b0 !important}
.w3-border-theme {border-color:#9c27b0 !important}

.w3-hover-theme:hover {color:#fff !important; background-color:#9c27b0 !important}
.w3-hover-text-theme:hover {color:#9c27b0 !important}
.w3-hover-border-theme:hover {border-color:#9c27b0 !important}

.w3-purple,.w3-hover-purple:hover{color:#fff!important;background-color:#9c27b0!important}
/*------------------   W3 Color theme --------------------------------------------*/

.blink-blue {color:#98bdf0 !important;animation:fading 1s infinite}@keyframes fading{0%{opacity:0}50%{opacity:1}100%{opacity:0}}
#td_sel_lang {width:100px}

</style>

<script>
//-----------------------------------------
var hconf = { lang: 1 };
var alang = {
  lang  : [ "Language", "Langue" ],
  supportsdist : [ "Distance between front/rear support",
  "Distance entre le support avant et arriere" ],
  supportsdist_type  : [ "(Natural number, millimeters)", "(Entier naturel, millimetres)" ],
  supportledist : [ "Distance between front support and leading edge",
  "Distance entre le support avant et le bord d'attaque" ],
  supportledist_type  : [ "(Natural number, millimeters)", "(Entier naturel, millimetres)" ],
  lcfrontcal       : [ "Load Cell front calibration",  "Calibrage de charge avant" ],
  lcfrontcal_type  : [ "Put a known weight", "Mettre un poids connu" ],
  lcfrontcal_help  : [ "Decimal number (gr)", "Entrez sa valeur (en g)" ],
  lcrearcal        : [ "Load Cell rear calibration", "Calibrage de charge arriere" ],
  lcrearcal_type   : [ "Put a known weight", "Mettre un poids connu" ],
  lcrearcal_help   : [ "Decimal number (gr)", "Entrez sa valeur (en g)" ],
  saveconf	: [ "Save config", "Sauvegarder config" ],
  resetconf : [ "Reset config", "Reinitialiser config" ],
  gps           : [ "GPS", "GPS" ],
  live          : [ "Live scale", "Vitesse" ],
  sats          : [ "Satellites", "Satellites" ],
  longitude     : [ "Rear weight", "Longitude" ],
  latitude      : [ "Front weight", "Latitude" ],
  vitesse       : [ "Weight", "Vitesse" ],
  vitessemax    : [ "CG from Leading Edge", "Vitesse max" ],
  nsat          : [ "CG from Leading Edge", "Nb satellites" ],
  alt           : [ "Altitude", "Altitude" ],
};
//-----------------------------------------
var screens = [ 'gps', 'live', 'sats' ];
//-----------------------------------------
function req( x, cb ) {
	var xhr = new XMLHttpRequest();
	xhr.open('GET', '/xhr?'+x);
  xhr.onerror = function() {
    //show_status( "error" );
  };
	xhr.onload = function() {
		if (xhr.status != 200) { // analyze HTTP status of the response
			console.log("Error "+xhr.status+": "+xhr.statusText);
		} else { // show the result
			if (cb)
				cb( JSON.parse(xhr.responseText) );
		}
	};
	xhr.send();
}
//-----------------------------------------
function gElt( n ) {
  return document.getElementById( n );
}
//-----------------------------------------
function drawCanvasBackground()
{
	const canvas = document.getElementById("myCanvas");
	const ctx = canvas.getContext("2d");
	const w = canvas.width;
	const h = canvas.height;
	const x = w/2;
	const y = h/2;
	const r = w/2 -10;
	
	drawCercle( ctx, x, y, r );
	drawCercle( ctx, x, y, r/3 );
	drawCercle( ctx, x, y, 2*r/3 );
}
//-----------------------------------------
function drawCercle(ctx, x, y, r )
{
	ctx.strokeStyle = "blue";
	ctx.beginPath();
	ctx.arc(x, y, r, 0, 2 * Math.PI);
	ctx.stroke(); 
}
//-----------------------------------------
function fillCercle(ctx, x, y, r, c )
{
	ctx.fillStyle = c;
	ctx.beginPath();
	ctx.arc(x, y, r, 0, 2 * Math.PI);
	ctx.fill(); 
}
//-----------------------------------------
function lang_refresh() {
  for (var k in alang) {
    var e = gElt( "lang_"+k );
    if (e) {
			e.innerHTML = alang[k][ hconf.lang ];
		}
  }
}
//-----------------------------------------
function iamhere( here ) {
  var e = gElt( "whereami" );
  var esrc = gElt( "lang_"+here );
  e.innerHTML = "GPSpeed: "+esrc.innerHTML;
  for (var i=0; i<screens.length; i++) {
	  hide_this( screens[i] );
  }
  if (here === "live")    live_on_vitesse();
  if (here === "gps")     live_on_gps();
  if (here === "sats")    live_on_sats();
  
  show_this( here );
  close_sidebar();
}
//-----------------------------------------
function clickReset() {
  console.log( "Reset max " );
  req( "resetMax=1" );
  coord_refresh();
}
//-----------------------------------------
var live_to = 0;
var live_type = "";
//-----------------------------------------
function coord_refresh() {
  var lon = gElt("live_longitude").innerHTML;
  var lat = gElt("live_latitude").innerHTML;
  var coord = "Coord. GPS : </br>"+String(lat)+", "+String(lon);
  gElt("lang_coord").innerHTML = coord;
}
//-----------------------------------------
function live_refresh_vitesse( h ) {
  if (h.err) {
    live_off();
    show_status("error_live", h.desc);
    iamhere("live");
    return;
  }
  var k, v, e, elt = ["vitesse","vitessemax"];
  for (i=0; i<elt.length; i++) {
    k = elt[i];
    e = gElt("live_"+k);
    if (e) {
      //if (! (v = h[k])) v = "?";
      v = h[k];
      e.innerHTML = v;
    }
  }
  //coord_refresh();
  if (live_to)					live_on_vitesse();
}
//-----------------------------------------
function live_refresh_gps( h ) {
  
  if (h.err) {
    live_off();
    show_status("error_live", h.desc);
    iamhere("live");
    return;
  }
  var k, v, e, elt = ["gpscoord", "gpslongitude","gpslatitude","gpsvitesse","gpsaltitude","gpsnbsats","gpsdate","gpstime","gpshdop"];
  for (i=0; i<elt.length; i++) {
    k = elt[i];
    e = gElt("lang_"+k+"_data");
    if (e) {
      //if (! (v = h[k])) v = "?";
      v = h[k];
      e.innerHTML = v;
    }
  }

  if (live_to)  					live_on_gps();
}
//-----------------------------------------
function live_refresh_sats( h ) {
  if (h.err) {
    live_off();
    show_status("error_live", h.desc);
    iamhere("live");
    return;
  }
  
  const canvas = document.getElementById("myCanvas");
  const ctx = canvas.getContext("2d");
  const W = canvas.width;
  const H = canvas.height;
  ctx.clearRect(0, 0, W, H);
  drawCanvasBackground();
  const R = W/2 -10;
  var ele, azi, snr;
  var alpha, x, y, r, c;
  
  for(i=0; i<h.sats.length; i++ )
  {
	
	ele = h.sats[i].ele;
	azi = h.sats[i].azi;
	snr = h.sats[i].snr;

	alpha = (azi) / 360.0 * 2 * Math.PI;
	r = (90.0-(ele))/90.0 * R;

	x = r * Math.cos(alpha) + W/2;
	y = r * Math.sin(alpha) + H/2;
	
  	c = "red";
  	if ( snr >5 )              c = "orange";
  	if ( snr >25 )             c = "green";


	fillCercle( ctx, x, y, 6, c );
  }
  //coord_refresh();
  if (live_to)					  	live_on_sats();
}
//-----------------------------------------
function live_on_vitesse() {
  live_off();
  live_type = "vitesse";
  live_to = setTimeout(
      function(){
        req( "getLiveVitesse=1", live_refresh_vitesse ); }
      , 500);
}
//-----------------------------------------
function live_on_sats() {
  live_off();
  live_type = "sats";
  live_to = setTimeout(
      function(){
        req( "getLiveSats=1", live_refresh_sats ); }
      , 500);
}
//-----------------------------------------
function live_on_gps() {
  live_off();
  live_type = "gps";
  live_to = setTimeout(
      function(){
        req( "getLiveGps=1", live_refresh_gps ); }
      , 500);
}
//-----------------------------------------
function live_off() {
  if (live_to) {
    clearTimeout( live_to );
    live_to = 0;
    live_type = "";
  }
}
//-----------------------------------------
function init_config() {
    iamhere( "live" );
	lang_refresh();
    //live_on();
}
//-----------------------------------------
var status_to = 0;
//-----------------------------------------
function show_status( key, p1, p2 ) {
  var langk = "status_"+key;
  var econtain = gElt("statusblock");
  var etxt = gElt("status");
  var txt = alang[ 'lang' ][ hconf.lang ];
  if (! p1) p1 = "";
  txt = txt.replace(/[$]1/, p1);
  if (p2) p2 = "";
  txt = txt.replace(/[$]2/, p2);
  etxt.innerHTML = txt;
  show_this( "statusblock" );
  if (status_to) { clearTimeout(status_to); }
  status_to = setTimeout( function() { hide_this("statusblock"); }, 2000 );
}
//-----------------------------------------
function show_this(k)	{
  var e = gElt(k);
  if (! e) { console.log( "show_this missing elt "+k ); }
  else { e.style.display="block"; }
}
//-----------------------------------------
function hide_this(k)	{
  var e = gElt(k);
  if (! e) { console.log( "hide_this missing elt "+k ); }
  else { e.style.display="none"; }
}
//-----------------------------------------
function close_sidebar() {hide_this("sidebar");console.log( "Fermeture");}
//-----------------------------------------
function init() {
  close_sidebar();
  init_config();
  iamhere('live');
  drawCanvasBackground();
  hide_this("sats");
}
//-----------------------------------------
console.log( "Print");
    </script>

  </head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
  <body onload="init();">
<!----------------------------------------------------------------->
    <nav class="w3-sidebar w3-bar-block w3-card" id="sidebar">
      <div class="w3-container w3-theme-d2">
				<span onclick="close_sidebar()" class="w3-button w3-display-topright w3-large">X</span><br>
        <br/>
			<a class="w3-bar-item w3-button" href="#" id="lang_live" onclick="iamhere('live')"></a>
			<a class="w3-bar-item w3-button" href="#" id="lang_gps" onclick="iamhere('gps')"></a>
			<a class="w3-bar-item w3-button" href="#" id="lang_sats" onclick="iamhere('sats')"></a>
			<hr/>
      </div>
    </nav>
    <header class="w3-bar w3-card w3-theme">
      <button class="w3-bar-item w3-button w3-xxxlarge w3-hover-theme"
        id="menu_button" onclick="show_this('sidebar')">&#9776;</button>
      <span class="w3-bar-item">
      </span>
  	  <h2 class="w3-bar-item" id="whereami"></h2>
    </header>
<!----------------------------------------------------------------->
    <div id="statusblock" class="w3-modal w3-animate-opacity">
      <div class="w3-modal-content w3-card-4">
        <header class="w3-container w3-theme-d2">
          <h5 id="status"></h5>
        </header>
      </div>
    </div>
<!----------------------------------------------------------------->
    <div class="w3-container w3-content">
<!----------------------------------------------------------------->
      <div id="live" class="w3-panel w3-white w3-card w3-display-container">
        <div id="titrelive" class="w3-panel w3-white w3-card w3-display-container w3-center w3-theme-l2">
        	<p>Vitesse max</p>
        </div>

        <table class="w3-table">
          <tr><td id="lang_coord">Coordonn&eacutees GPS :</td>
          <td></td></tr>
          <!---
          <tr><td id="lang_latitude"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xlarge w3-theme-dark w3-right-align" id="live_latitude">45.21258</span></td></tr>
          <tr><td id="lang_longitude"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xlarge w3-theme-dark w3-right-align" id="live_longitude">0.008652</span></td></tr>
          --->
          <tr><td id="lang_vitessemax"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xlarge w3-theme-dark w3-right-align" id="live_vitessemax"></span></td></tr>
          <tr><td id="lang_vitesse"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xlarge w3-theme-dark w3-right-align" id="live_vitesse"></span></td></tr>
          <!---
          <tr><td id="lang_nsat"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xlarge w3-theme-dark w3-right-align" id="live_nsat"></span></td></tr>
          <tr><td id="lang_alt"></td>
            <td class="w3-right-align"><span class="w3-tag w3-xlarge w3-theme-dark w3-right-align" id="live_alt"></span></td></tr>
          --->
        </table>


        <div id="buttons" class="w3-panel w3-white w3-card w3-display-container w3-center">
          <div>&nbsp</div>
          <div>
              <button class="w3-button w3-border w3-round-large w3-hover-purple w3-theme-l4 "
                onclick="clickReset()">
                <span>Reset vitesse max</span>
              </button>
          </div>
          <div>&nbsp</div>
        </div>
      </div>
<!----------------------------------------------------------------->
      <div id="sats" class="w3-panel w3-white w3-card w3-display-container">
        <div id="titlegps" class="w3-panel w3-white w3-card w3-display-container w3-center w3-theme-l2">
          <p><span class="w3-center-align">Position des satellites</span></p>
        </div>
        <div class="w3-center-align w3-block" style = "text-align:center;">
          <canvas id="myCanvas" width="350" height="350" style="border:1px solid #000000;">
          Your browser does not support the HTML canvas tag.
          </canvas>
          <p></p>
        </div>
      </div>
<!----------------------------------------------------------------->
      <div id="gps" class="w3-panel w3-white w3-card w3-display-container">
        <div id="titlegps" class="w3-panel w3-white w3-card w3-display-container w3-center w3-theme-l2">
          <p>Datas GPS  (BN-220)</p>
        </div>
        <table class="w3-table">
          <tr><td id="lang_gpscoord">Coordonn&eacutees GPS : </td>
            <td id="lang_gpscoord_data" class="w3-right-align">45.1256N, 0.123695E</td></tr>
          <tr><td id="lang_gpslatitude">Lattitude :</td>
            <td id="lang_gpslatitude_data" class="w3-right-align">45.1256N</td></tr>
          <tr><td id="lang_gpslongitude">Longitude :</td>
            <td id="lang_gpslongitude_data" class="w3-right-align">0.123695E</td></tr>
          <tr><td id="lang_gpsvitesse">Vitesse :</td>
            <td id="lang_gpsvitesse_data" class="w3-right-align">23.12km/h</td></tr>
          <tr><td id="lang_gpsaltitude">Altitude :</td>
            <td id="lang_gpsaltitude_data" class="w3-right-align">67.2m</td></tr>
          <tr><td id="lang_gpsnbsats">Nb satellites :</td>
            <td id="lang_gpsnbsats_data" class="w3-right-align">8</td></tr>
          <tr><td id="lang_gpsdate">Date :</td>
            <td id="lang_gpsdate_data" class="w3-right-align">17/11/2023</td></tr>
          <tr><td id="lang_gpstime">Heure :</td>
            <td id="lang_gpstime_data" class="w3-right-align">16:45:23</td></tr>
          <tr><td id="lang_gpshdop">HDOP :</td>
            <td id="lang_gpshdop_data" class="w3-right-align">0.98</td></tr>
        </table>
      </div>
<!----------------------------------------------------------------->
    </div>
  </body>
</html>
)=====";


 
