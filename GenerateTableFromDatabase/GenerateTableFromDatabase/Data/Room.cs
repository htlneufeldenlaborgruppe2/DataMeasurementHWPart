//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace GenerateTableFromDatabase.Data
{
    using System;
    using System.Collections.Generic;
    
    public partial class Room
    {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2214:DoNotCallOverridableMethodsInConstructors")]
        public Room()
        {
            this.Room_Device = new HashSet<Room_Device>();
        }
    
        public int Room_ID { get; set; }
        public string RoomNr { get; set; }
        public Nullable<decimal> NoiseConstant { get; set; }
        public int WorkingPlaces { get; set; }
        public Nullable<int> SeatsBehind { get; set; }
    
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly")]
        public virtual ICollection<Room_Device> Room_Device { get; set; }
    }
}
