var speed = 5;
const APIKEY = "45697832";
const SESSIONID = "2_MX40NTY5NzgzMn5-MTQ3NTc2MTg4MDU2OH5oQjhUb0t0UUhYLzV4elV3ZWF5UGxSSk5-fg"; 
const TOKEN = "T1==cGFydG5lcl9pZD00NTY5NzgzMiZzZGtfdmVyc2lvbj10YnBocC12MC45MS4yMDExLTA3LTA1JnNpZz1hYzMyMDk3YTkyODM4ZDY3YjdjYmQyZTg1NjY4OTczYjllYmIwMmEzOnNlc3Npb25faWQ9Ml9NWDQwTlRZNU56Z3pNbjUtTVRRM05UYzJNVGc0TURVMk9INW9RamhVYjB0MFVVaFlMelY0ZWxWM1pXRjVVR3hTU2s1LWZnJmNyZWF0ZV90aW1lPTE0NzU3NjE2Njkmcm9sZT1tb2RlcmF0b3Imbm9uY2U9MTQ3NTc2MTY2OS4wNjQyMTQ1NjQ0ODA5MyZleHBpcmVfdGltZT0xNDc4MzUzNjY5";
const HOST = 'http://192.168.242.71';
var active = {
	up: false,
	down: false, 
	left: false,
	right: false
};
function moveTo(direction) {
	$.ajax({
		type: 'POST',
		url: HOST + '/move/' + direction
	})
	.done(function () {
		setTimeout(function() {
			if (active[direction]) {
				moveTo(direction);
			}
		}, 100 / speed);
	});			
}

$(function() {
	var session = OT.initSession(APIKEY, SESSIONID);
	session.connect(TOKEN, function() {
		alert('connected to Robot room');
	});
	session.on('streamCreated', function (event) {
		alert('connected to Robot video');
		session.subscribe(event.stream, 'videoDiv');
	});

	$('.control').mousedown(function(event) {
		var direction = $(this).attr('data-direction');
		active[direction] = true;
		moveTo(direction);
	});
	$('.control').mouseup(function(event) {
		var direction = $(this).attr('data-direction');
		active[direction] = false;					
	});
	
	$('.speedUp').click(function() {
		if (speed < 10) {
			speed++;
		}
	});
	$('.speedDown').click(function() {
		if (speed > 1) {
			speed--;
		}
	});
});
