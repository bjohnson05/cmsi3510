   public class Simple2Threads {

      static int parentTime = 5000;
      static int childTime  = 3000;

      public static void main( String[] args ) {

         if( args.length == 1 ) {
            parentTime = Integer.parseInt( args[0] ) * 1000;
         } else if( args.length == 2 ) {
            parentTime = Integer.parseInt( args[0] ) * 1000;
            childTime  = Integer.parseInt( args[1] ) * 1000;
         }
         System.out.println( "\n...Starting program Simple2threads [in java]..." );
         System.out.println( "......Parent started, will start child then sleep " + parentTime + " milliseconds..." );

         Thread childThread = new Thread( new Runnable() {
            public void run() {
               System.out.println( "......Child started, sleeping " + childTime + " milliseconds..." );
               sleep( childTime );
               System.out.println( "......Child is done sleeping " + childTime/1000 + " seconds.\n" );
            }
         });

         System.out.println( "\n......Starting child thread..." );
         childThread.start();
         sleep( parentTime );
         System.out.println("......Parent is done sleeping " + parentTime/1000 + " seconds.\n\n");

      }
      private static void sleep( int milliseconds ) {
         try{
            Thread.sleep( milliseconds );
         } catch( InterruptedException ie ) {
            // ignore this exception; it won't happen anyhow
         }
      }
   }
