package bean;

public class Bill {
	private double total = 0;
	private double totalUpload = 0;
	private double totalDownload = 0;
	private double totalBillAmount = 0;
	private double excessData = 0;
	private double excessCharge = 0;
	private String Plan = null;
	public double getTotal() {
		return total;
	}
	public void setTotal(double total) {
		this.total = total;
	}
	public double getTotalUpload() {
		return totalUpload;
	}
	public void setTotalUpload(double totalUpload) {
		this.totalUpload = totalUpload;
	}
	public double getTotalDownload() {
		return totalDownload;
	}
	public void setTotalDownload(double totalDownload) {
		this.totalDownload = totalDownload;
	}
	public double getTotalBillAmount() {
		return totalBillAmount;
	}
	public void setTotalBillAmount(double totalBillAmount) {
		this.totalBillAmount = totalBillAmount;
	}
	public double getExcessData() {
		return excessData;
	}
	public void setExcessData(double excessData) {
		this.excessData = excessData;
	}
	public double getExcessCharge() {
		return excessCharge;
	}
	public void setExcessCharge(double excessCharge) {
		this.excessCharge = excessCharge;
	}
	public String getPlan() {
		return Plan;
	}
	public void setPlan(String plan) {
		Plan = plan;
	}
	
	
}
