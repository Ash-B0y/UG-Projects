
//Used to check the credentials and session management
application.controller("RouteController", function($scope, $http, $window,
		$cookies) {

	$scope.login = {};
	$scope.login.userName = null;
	$scope.login.password = null;
	$scope.login.message = null;

	$scope.login.loginForm = function() {

		$scope.login.message = null;
		var jsonString = angular.toJson($scope.login)
		
		$http.post(URI + "Mediation/authentication", jsonString).then(
				function(response) {
					
					
					$cookies.put('name', $scope.login.userName);

					$scope.login.message = response.data.message;

					
					if (response.data.role == 'A')
						$window.location.href = "partials/administrator.html";
					else if (response.data.role == 'C')
						$window.location.href = "partials/customer.html";

				}, function(response) {
					$scope.login.message = response.data.role;

				})

	}
	$('.btn').on('click', function() {
		var $this = $(this);
		$this.button('loading');
		setTimeout(function() {
			$this.button('reset');
		}, 5000);
	})

});


// Used to add new users in db
application.controller("AddUserController", function($scope, $http, $cookies) {
	$scope.addUserForm = {};
	$scope.addUserForm.fullName = null;
	$scope.addUserForm.contactNo = null;
	$scope.addUserForm.packages = null;
	$scope.addUserForm.userName = null;
	$scope.addUserForm.password = null;
	$scope.addUserForm.dateofbirth = null;
	$scope.addUserForm.address = null;
	$scope.addUserForm.emailId = null;
	$scope.addUserForm.mac = null;
	$scope.addUserForm.message = null;
	$scope.addUserForm.submitForm = function() {

		$scope.addUserForm.message = null;
		var jsonString = angular.toJson($scope.addUserForm)
		
		$http.post(URI + "Mediation/adduser", jsonString).then(
				function(response) {
					$scope.addUserForm.message = response.data.message;
					
				}, function(response) {
					$scope.addUserForm.message = response.data.message;

				})

	}

});


//Used to get all user details and modify user details
application.controller("viewController", function($scope, $http,$cookies) {
	$scope.user = {};
	$scope.user.getUser = function() {
		$http.get(URI + "Mediation/getAllUser").then(function(response) {
			$scope.userData = response.data;

		}, function(response) {
			$scope.userErrorMessage = response.data.message;

		});

	}
	$scope.userClick = function(event) {
		$scope.myVar = angular.element(event.target).text();
	};
	$scope.updateUser = function(mac){
		$scope.userUpdate={}
		$scope.userUpdate.mac = mac;
		$scope.userUpdate.fullName = document.getElementById("fname").value;
		$scope.userUpdate.contactNo = document.getElementById("contactno").value;
		$scope.userUpdate.emailId = document.getElementById("email").value;
		$scope.userUpdate.packages = document.getElementById("plan").value;
		$scope.userUpdate.address = document.getElementById("location").value;
		
		var jsonString = angular.toJson($scope.userUpdate)
		$http.post(URI + "Mediation/userUpdate", jsonString).then(
				function(response) {
					$scope.userUpdate.message = response.data.message;
					
				}, function(response) {
					$scope.userUpdate.message = response.data.message;

				})
	}

});


//Admin AllUserperformance chart controller
application.controller("chartController", function($scope, $http,$cookies) {
	
	$scope.getAllSession = function(){
		$http.get(URI + "Mediation/getAllUserData").then(
				function(response) {						
					$scope.userData = response.data;
					
				}, function(response) {
					$scope.userErrorMessage = response.data.message;
					
				});
	}
	google.charts.load("current", {
		packages : [ 'corechart' ]
	});
	$scope.click = function() {
		google.charts.setOnLoadCallback(drawChart_Interface);
	}
	function drawChart_Interface() {

		var data = new google.visualization.DataTable();
		data.addColumn('string', 'Person');
		data.addColumn('number', 'MB Used');
		
		for (i = 0; i < $scope.userData.length; i++) {
			data.addRow([ $scope.userData[i].userName, $scope.userData[i].totalDataUsed ])		
		}
		var options = {
			title : 'Total Data Used By the Users (In GB)',
			width : 600,
			height : 600,
			legend : 'none',
			vAxis : {
				title : "Data Used in MB",
				titleTextStyle : {
					color : "green"
				}
			},
			hAxis : {
				title : "Users",
				titleTextStyle : {
					color : "green"
				}
			},
			lineWidth : 1
		}
		var chart = new google.visualization.PieChart(document
				.getElementById('chart_div_interface'));
		chart.draw(data, options);

	}
});


//Used to Fetch user details
applicationCustomer.controller("userdetailsController", function($scope, $http,$cookies) {
	$scope.user = {};
	$scope.user.userName = $cookies.get('name');
	$scope.myDetails = function() {
		var data = angular.toJson($scope.user);
		$http.post(URI + "Mediation/displayUserDetails", data).then(
				function(response) {
					$scope.userDetails = response.data;

				}, function(response) {
					$scope.userErrorMessage = response.data.message;

				});
	}

});



//Used to generate user bill history
applicationCustomer.controller("billUsageController", function($scope, $http,$cookies) {
	$scope.user = {};
	$scope.user.userName =  $cookies.get('name');
	var data = angular.toJson($scope.user);
	$scope.collectSession = function() {
		$http.post(URI + "Mediation/getallUserSessions", data).then(
				function(response) {
					$scope.userAllSessionData = response.data;

				}, function(response) {
					
					$scope.userErrorMessage = response.data.message;

				});
	}
	$scope.weekBillChart = function() {
		$scope.filterWeekData = [];
		var weekday = new Date(2018, 7, 21)
		for (var i = 0; i < $scope.userAllSessionData.length; i++) {
			var date1 = new Date($scope.userAllSessionData[i].sessionDate);
			if (weekday <= date1) {
				$scope.filterWeekData.push($scope.userAllSessionData[i])
			}

			google.charts.load("current", {
				packages : [ 'corechart' ]
			});

			google.charts.setOnLoadCallback(drawChart_Interface);

			function drawChart_Interface() {

				var data = new google.visualization.DataTable();
				data.addColumn('string', 'Day');
				data.addColumn('number', 'MB Used');

				for (i = 0; i < $scope.filterWeekData.length; i++) {
					data.addRow([ $scope.filterWeekData[i].sessionDate,
							$scope.filterWeekData[i].total ])
				}
				var options = {
					title : 'Week bill',
					width : 600,
					height : 600,
					legend : 'none',
					vAxis : {
						title : "Data Used in MB",
						titleTextStyle : {
							color : "green"
						}
					},
					hAxis : {
						title : "Day",
						titleTextStyle : {
							color : "green"
						}
					},
					lineWidth : 1
				}
				var chart = new google.visualization.ColumnChart(document
						.getElementById('weekBill'));
				chart.draw(data, options);

			}

		}
	}

	$scope.sixMonthBillChart = function() {
		$scope.filterSixMonthData = [];
		$scope.feb = {};
		$scope.feb.month = "February";
		$scope.feb.data = 0;
		$scope.mar = {};
		$scope.mar.month = "March";
		$scope.mar.data = 0;
		$scope.apr = {};
		$scope.apr.month = "April";
		$scope.apr.data = 0;
		$scope.may = {};
		$scope.may.month = "May";
		$scope.may.data = 0;
		$scope.june = {};
		$scope.june.month = "June";
		$scope.june.data = 0;
		$scope.july = {};
		$scope.july.month = "July";
		$scope.july.data = 0;
		for (var i = 0; i < $scope.userAllSessionData.length; i++) {
			var date = new Date($scope.userAllSessionData[i].sessionDate);
			var month = date.getMonth();
			switch (month) {
			case 1:
				$scope.feb.data += $scope.userAllSessionData[i].total/1024;
				break;
			case 2:
				$scope.mar.data += $scope.userAllSessionData[i].total/1024;
				break;
			case 3:
				$scope.apr.data += $scope.userAllSessionData[i].total/1024;
				break;
			case 4:
				$scope.may.data += $scope.userAllSessionData[i].total/1024;
				break;
			case 5:
				$scope.june.data += $scope.userAllSessionData[i].total/1024;
				break;
			case 6:
				$scope.july.data += $scope.userAllSessionData[i].total/1024;
				break;
			}
		}
		$scope.filterSixMonthData.push($scope.feb, $scope.mar, $scope.apr,
				$scope.may, $scope.june, $scope.july)
		

		google.charts.load("current", {
			packages : [ 'corechart' ]
		});

		google.charts.setOnLoadCallback(month_chart);

		function month_chart() {

			var data = new google.visualization.DataTable();
			data.addColumn('string', 'Month');
			data.addColumn('number', 'GB Used');

			for (i = 0; i < $scope.filterSixMonthData.length; i++) {
				data.addRow([ $scope.filterSixMonthData[i].month,
						$scope.filterSixMonthData[i].data ])
			}
			var options = {
				title : 'Month bill',
				width : 600,
				height : 600,
				legend : 'none',
				vAxis : {
					title : "Data Used in GB",
					titleTextStyle : {
						color : "green"
					}
				},
				hAxis : {
					title : "Month",
					titleTextStyle : {
						color : "green"
					}
				},
				lineWidth : 1
			}
			var chart = new google.visualization.ColumnChart(document
					.getElementById('sixMonthBill'));
			chart.draw(data, options);
		}
	}
	
	$scope.thisMonthBillChart = function(){
		$scope.filterMonthData = [];
		var thisMonth = new Date().getMonth()
		for (i = 0; i < $scope.userAllSessionData.length; i++) {
			sessionMonth = new Date($scope.userAllSessionData[i].sessionDate).getMonth();
			if(sessionMonth == thisMonth){
				$scope.filterMonthData.push($scope.userAllSessionData[i])
			}
		}
		$scope.weekData = [];
		$scope.first = {}
		$scope.first.day = "First week";
		$scope.first.data = 0;
		$scope.second = {}
		$scope.second.day = "Second week";
		$scope.second.data = 0;
		$scope.third = {}
		$scope.third.day = "Third week";
		$scope.third.data = 0;
		$scope.fourth = {}
		$scope.fourth.day = "Fourth week";
		$scope.fourth.data = 0;
		for (i = 0; i < $scope.filterMonthData.length; i++) {
			var day = new Date($scope.filterMonthData[i].sessionDate).getDate();
			if(day>=1 && day<=7){
				$scope.first.data+=$scope.filterMonthData[i].total
			}
			else if(day>=8 && day<=14){
				$scope.second.data+=$scope.filterMonthData[i].total
			}
			else if(day>=15 && day<=21){
				$scope.third.data+=$scope.filterMonthData[i].total
			}
			else{
				$scope.fourth.data+=$scope.filterMonthData[i].total
			}
			
		}
		$scope.weekData.push($scope.first,$scope.second,$scope.third,$scope.fourth)
		
		
		google.charts.load("current", {
			packages : [ 'corechart' ]
		});

		google.charts.setOnLoadCallback(month_chart);

		function month_chart() {

			var data = new google.visualization.DataTable();
			data.addColumn('string', 'Week');
			data.addColumn('number', 'MB Used');

			for (i = 0; i < $scope.weekData.length; i++) {
				data.addRow([ $scope.weekData[i].day,
						$scope.weekData[i].data ])
			}
			var options = {
				title : 'This Month Bill',
				width : 600,
				height : 600,
				legend : 'none',
				vAxis : {
					title : "Data Used in MB",
					titleTextStyle : {
						color : "green"
					}
				},
				hAxis : {
					title : "Week",
					titleTextStyle : {
						color : "green"
					}
				},
				lineWidth : 1
			}
			var chart = new google.visualization.LineChart(document
					.getElementById('thisMonthBill'));
			chart.draw(data, options);
	}
	}
});

//To Generate bill
applicationCustomer.controller("billGeneratorController", function($scope, $http,$cookies) {
	$scope.customer = {};
	$scope.customer.userName =  $cookies.get('name');
	$scope.userTable = function() {
		var data = angular.toJson($scope.customer);
		$http.post(URI + "Mediation/generateUserBillTable", data).then(
				function(response) {
					
					$scope.customerDetails = response.data;

				}, function(response) {

					$scope.customerErrorMessage = response.data.message;

				});
	}
	
});

//session management
application.controller("CookieController",function($scope, $http, $cookies) {
	$scope.getUserName = function() {

		if($cookies.get('name')==null){
			window.location="../error.html";
		}
		else{
			$scope.username = $cookies.get('name');
		}
	}
	
	$scope.logout = function() {
		alert("Successfully logged out");
		$cookies.remove("name",{ path: '/Project_billing_group9' });
		window.location="../index.html";
	}
});


applicationCustomer.controller("CookieControllerCustomer",function($scope, $http, $cookies) {
	$scope.getUserName = function() {

		if($cookies.get('name')==null){
			window.location="../error.html";
		}
		else{

			$scope.username = $cookies.get('name');
		}
	}
	
	$scope.logout = function() {
		alert("Successfully logged out");
		$cookies.remove("name",{ path: '/Project_billing_group9' });
		window.location="../index.html";
	}
});

