package jp.co.worksap.intern.entities.staff;

import jp.co.worksap.intern.entities.ICsvMasterDTO;

public class StaffDTO implements ICsvMasterDTO {
	/**
	 * 
	 */
	private static final long serialVersionUID = -8538243149394207296L;
	
	private Long staffId;
	private String name;
	private String gender;
	private RankType rank;
	private PositionType position;
	private Long hotelId;

	/**
	 * Default Constructor
	 * 
	 * @param staffId
	 * @param name
	 * @param gender
	 * @param rank
	 * @param position
	 * @param hotelId
	 */
	public StaffDTO(Long staffId, String name, String gender,
			RankType rank, PositionType position, Long hotelId) {
		super();
		this.staffId = staffId;
		this.name = name;
		this.gender = gender;
		this.rank = rank;
		this.position = position;
		this.hotelId = hotelId;
	}

	public Long getStaffId() {
		return staffId;
	}

	public String getName() {
		return name;
	}

	public String getGender() {
		return gender;
	}

	public RankType getRank() {
		return rank;
	}

	public PositionType getPosition() {
		return position;
	}

	public Long getHotelId() {
		return hotelId;
	}

}
