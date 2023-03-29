#include "PlayLevel.h"
#include "WeaponSheep.h"
#include "WeaponBazooka.h"
#include "WeaponTorch.h"
#include "WeaponDrill.h"
#include "Map.h"
#include "Player.h"
#include "WeaponShotgun.h"
#include "WeaponGrenade.h"
#include "ContentsEnums.h"
#include "MapModifier.h"
#include "GlobalValue.h"
#include "Leaf.h"
#include "WeaponHandgun.h"
#include "WeaponUzi.h"
#include "WeaponInterFace.h"
#include "WeaponAirStrike.h"
#include "HomingMissile.h"
#include "WeaponMinigun.h"
#include "WindUI.h"
#include "WeaponClusterBomb.h"
#include "AllPlayerHpUI.h"
#include "TurnTimeUI.h"
#include "WeaponFirePunch.h"


#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>


GlobalValue GlobalValue::gValue;

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::SoundLoad()
{

}

void PlayLevel::ImageLoad()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	GameEngineDirectory InterFace;
	InterFace.MoveParentToDirectory("ContentsResources");
	InterFace.Move("ContentsResources");
	InterFace.Move("Image");
	InterFace.Move("InterFace");

	{
		Dir.Move("Map");

        //Map & ColMap
		GameEngineImage* MapImage1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity.bmp"));
		GameEngineImage* ColMapImage1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCity_Ground.bmp"));
	
		GameEngineImage* MapImage2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapBooks.bmp"));
        GameEngineImage* ColMapImage2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapBooks_Ground.bmp"));

		GameEngineImage* MapImage3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCars.bmp"));
		GameEngineImage* ColMapImage3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapCars_Ground.bmp"));

		GameEngineImage* MapImage4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapTrain.bmp"));
		GameEngineImage* ColMapImage4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapTrain_Ground.bmp"));

        //BackGround
		GameEngineImage* sky = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("gradient.bmp"));
	
		GameEngineImage* Mountain = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Midground.bmp"));
        Mountain->Cut(4, 1);

		GameEngineImage* Water = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Under_Water.bmp"));

		GameEngineImage* Wave = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Water_sprite.bmp"));
        Wave->Cut(1, 11);

        //Map Objects
        GameEngineImage* MapObj1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject1.bmp"));
        GameEngineImage* MapObjCol1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject1_Col.bmp"));

        GameEngineImage* MapObj2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject2.bmp"));
        GameEngineImage* MapObjCol2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject2_Col.bmp"));

        GameEngineImage* MapObj3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject3.bmp"));
        GameEngineImage* MapObjCol3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MapObject3_Col.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ScatterLeaf.bmp"));
		Image->Cut(5, 3);
	}
    Dir.MoveParent();
    //ItemImage
    {
        Dir.Move("item");
        {

            GameEngineImage* Medikit = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("mcrate1.bmp"));
            Medikit->Cut(1, 12);

            GameEngineImage* FlyingMedikit = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("mcrate2.bmp"));
            FlyingMedikit->Cut(1, 20);
        }

        Dir.MoveParent();
    }

	{
		Dir.Move("Weapon");

		GameEngineImage* bazooka = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazooka.bmp"));
		GameEngineImage* bazookaRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazookaRot.bmp"));

		GameEngineImage* Airplane = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Airplane.bmp"));
		GameEngineImage* AirplaneRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirplaneRight.bmp"));


		GameEngineImage* sheepWalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepWalkRight.bmp"));
		sheepWalkRight->Cut(1, 8);
		GameEngineImage* sheepWalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepWalkLeft.bmp"));
		sheepWalkLeft->Cut(1, 8);

		GameEngineImage* AirMissile = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirMissile.bmp"));
		GameEngineImage* AirMissileRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirMissileRot.bmp"));


        GameEngineImage* HomingBlue = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingBlue.bmp"));
        GameEngineImage* HomingRed = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingRed.bmp"));
        GameEngineImage* HomingRot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HomingRot.bmp"));

        GameEngineImage* fire = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Fire.bmp"));
        GameEngineImage* marker = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("marker.bmp"));
        marker->Cut(1, 10);

		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AimingLine.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AimingLineRot.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TempBomb.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grenade.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeRot.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Clusterbomb.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterbombRot.bmp"));
        GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("cluster.bmp"));
		GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("clusterRot.bmp"));


        //무기 효과
        Dir.Move("Effect");
        {
		    GameEngineImage* BazSmoke = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BazSmoke.bmp"));
		    BazSmoke->Cut(1, 64);

            GameEngineImage* Charging = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Charging.bmp"));
            Charging->Cut(1, 16);

            GameEngineImage* circle50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("circle50.bmp"));
            circle50->Cut(1, 9);

            GameEngineImage* elipse50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("elipse50.bmp"));
            elipse50->Cut(1, 20);

            GameEngineImage* Smoke50 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Smoke50.bmp"));
            Smoke50->Cut(1, 28);

            GameEngineImage* Smoke100 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Smoke100.bmp"));
            Smoke100->Cut(1, 28);

            GameEngineImage* Poot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Poot.bmp"));
            Poot->Cut(1, 18);

            GameEngineImage* Spark1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Spark1.bmp"));
            Spark1->Cut(1, 32);

            GameEngineImage* Spark2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Spark2.bmp"));
            Spark2->Cut(1, 32);

            GameEngineImage* Biff = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Biff.bmp"));
            Biff->Cut(1, 12);

            GameEngineImage* Pow = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Pow.bmp"));
            Pow->Cut(1, 18);

            GameEngineImage* ChargeAni = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ChargeAni.bmp"));
            ChargeAni->Cut(1, 16);

            GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ChargeAniRot.bmp"));

            Dir.MoveParent();
        }


		Dir.MoveParent();
	}
	{
		Dir.Move("Player");
		Dir.Move("Image");
        {
            //Grave 이미지
            GameEngineImage* Grave1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave1.bmp"));
            Grave1->Cut(1, 20);
            GameEngineImage* Grave2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave2.bmp"));
            Grave2->Cut(1, 20);
            GameEngineImage* Grave3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave3.bmp"));
            Grave3->Cut(1, 20);
            GameEngineImage* Grave4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave4.bmp"));
            Grave4->Cut(1, 20);
            GameEngineImage* Grave5 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave5.bmp"));
            Grave5->Cut(1, 20);
            GameEngineImage* Grave6 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Grave6.bmp"));
            Grave6->Cut(1, 20);
        }
        {
            //플레이어 이미지
            GameEngineImage* FacePlant = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FacePlant.bmp"));
            FacePlant->Cut(1, 49);
        }
		{
			//Left 플레이어 이미지
			GameEngineImage* IdleLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleLeft.bmp"));
			IdleLeft->Cut(1, 6);
			GameEngineImage* WalkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkLeft.bmp"));
			WalkLeft->Cut(1, 15);		
			GameEngineImage* JumpReadyLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("JumpReadyLeft.bmp"));
			JumpReadyLeft->Cut(1, 10);
            GameEngineImage* DieLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DieLeft.bmp"));
            DieLeft->Cut(1, 60);
            GameEngineImage* WinLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WinLeft.bmp"));
            WinLeft->Cut(1, 14);

			GameEngineImage* FlyUpLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyupLeft.bmp"));
			FlyUpLeft->Cut(1, 2);
            GameEngineImage* FlyLinkLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyLinkLeft.bmp"));
            FlyLinkLeft->Cut(1, 7);
			GameEngineImage* FlyDownLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlydownLeft.bmp"));
			FlyDownLeft->Cut(1, 2);

            GameEngineImage* FlyAwayLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyAwayLeft.bmp"));
            FlyAwayLeft->Cut(1, 32);
            GameEngineImage* SlideLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SlideLeft.bmp"));
            SlideLeft->Cut(1, 3);
            GameEngineImage* StandUpLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StandUpLeft.bmp"));
            StandUpLeft->Cut(1, 22);

			GameEngineImage* bazAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimLeft.bmp"));
			bazAimLeft->Cut(1, 32);
			GameEngineImage* bazOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffLeft.bmp"));
			bazOffLeft->Cut(1, 7);
			GameEngineImage* bazOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnLeft.bmp"));
			bazOnLeft->Cut(1, 8);

            GameEngineImage* sheepOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOffLeft.bmp"));
            sheepOffLeft->Cut(1, 10);
            GameEngineImage* sheepOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOnLeft.bmp"));
            sheepOnLeft->Cut(1, 10);

            GameEngineImage* AirStrikeOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOffLeft.bmp"));
            AirStrikeOffLeft->Cut(1, 10);
            GameEngineImage* AirStrikeOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOnLeft.bmp"));
            AirStrikeOnLeft->Cut(1, 10);

            GameEngineImage* homingAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingAimLeft.bmp"));
            homingAimLeft->Cut(1, 32);
            GameEngineImage* homingOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOffLeft.bmp"));
            homingOffLeft->Cut(1, 7);
            GameEngineImage* homingOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOnLeft.bmp"));
            homingOnLeft->Cut(1, 7);

            GameEngineImage* GrenadeAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeAimLeft.bmp"));
            GrenadeAimLeft->Cut(1, 32);
            GameEngineImage* GrenadeOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOffLeft.bmp"));
            GrenadeOffLeft->Cut(1, 10);
            GameEngineImage* GrenadeOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOnLeft.bmp"));
            GrenadeOnLeft->Cut(1, 10);

            GameEngineImage* TorchFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchFireLeft.bmp"));
            TorchFireLeft->Cut(1, 15);
            GameEngineImage* TorchOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOffLeft.bmp"));
            TorchOffLeft->Cut(1, 15);
            GameEngineImage* TorchOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOnLeft.bmp"));
            TorchOnLeft->Cut(1, 15);

            GameEngineImage* DrillLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillLeft.bmp"));
            DrillLeft->Cut(1, 4);
            GameEngineImage* DrillOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOffLeft.bmp"));
            DrillOffLeft->Cut(1, 13);
            GameEngineImage* DrillOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOnLeft.bmp"));
            DrillOnLeft->Cut(1, 13);

            GameEngineImage* UziAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziAimLeft.bmp"));
            UziAimLeft->Cut(1, 32);
            GameEngineImage* UziFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziFireLeft.bmp"));
            UziFireLeft->Cut(1, 32);
            GameEngineImage* UziOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOffLeft.bmp"));
            UziOffLeft->Cut(1, 10);
            GameEngineImage* UziOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOnLeft.bmp"));
            UziOnLeft->Cut(1, 10);

            GameEngineImage* ClusterBombAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombAimLeft.bmp"));
            ClusterBombAimLeft->Cut(1, 32);
            //GameEngineImage* ClusterBombFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombFireLeft.bmp"));
            //ClusterBombFireLeft->Cut(1, 32);
            GameEngineImage* ClusterBombOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOffLeft.bmp"));
            ClusterBombOffLeft->Cut(1, 10);
            GameEngineImage* ClusterBombOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOnLeft.bmp"));
            ClusterBombOnLeft->Cut(1, 10);

            GameEngineImage* HandgunAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunAimLeft.bmp"));
            HandgunAimLeft->Cut(1, 32);
            GameEngineImage* HandgunFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunFireLeft.bmp"));
            HandgunFireLeft->Cut(1, 32);
            GameEngineImage* HandgunOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOffLeft.bmp"));
            HandgunOffLeft->Cut(1, 10);
            GameEngineImage* HandgunOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOnLeft.bmp"));
            HandgunOnLeft->Cut(1, 10);

            GameEngineImage* MinigunAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunAimLeft.bmp"));
            MinigunAimLeft->Cut(1, 32);
            GameEngineImage* MinigunFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunFireLeft.bmp"));
            MinigunFireLeft->Cut(1, 32);
            GameEngineImage* MinigunOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOffLeft.bmp"));
            MinigunOffLeft->Cut(1, 10);
            GameEngineImage* MinigunOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOnLeft.bmp"));
            MinigunOnLeft->Cut(1, 10);

            GameEngineImage* ShotgunAimLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunAimLeft.bmp"));
            ShotgunAimLeft->Cut(1, 32);
            GameEngineImage* ShotgunFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunFireLeft.bmp"));
            ShotgunFireLeft->Cut(1, 32);
            GameEngineImage* ShotgunOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOffLeft.bmp"));
            ShotgunOffLeft->Cut(1, 10);
            GameEngineImage* ShotgunOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOnLeft.bmp"));
            ShotgunOnLeft->Cut(1, 10);
            
            GameEngineImage* FirePunchChargingLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchChargingLeft.bmp"));
            FirePunchChargingLeft->Cut(1, 9);
            GameEngineImage* FirePunchFireLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchFireLeft.bmp"));
            FirePunchFireLeft->Cut(1, 3);
            GameEngineImage* FirePunchOffLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOffLeft.bmp"));
            FirePunchOffLeft->Cut(1, 26);
            GameEngineImage* FirePunchOnLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOnLeft.bmp"));
            FirePunchOnLeft->Cut(1, 26);
            GameEngineImage* FirePunchAfterLeft = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchAfterLeft.bmp"));
            FirePunchAfterLeft->Cut(1, 13);

		}

		{
			//Right 플레이어 이미지
			GameEngineImage* IdleRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("IdleRight.bmp"));
			IdleRight->Cut(1, 6);
			GameEngineImage* WalkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WalkRight.bmp"));
			WalkRight->Cut(1, 15);
			GameEngineImage* JumpReadyRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("JumpReadyRight.bmp"));
			JumpReadyRight->Cut(1, 10);
            GameEngineImage* DieRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DieRight.bmp"));
            DieRight->Cut(1, 60);
            GameEngineImage* WinRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WinRight.bmp"));
            WinRight->Cut(1, 14);
			GameEngineImage* FlyUpRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyupRight.bmp"));
			FlyUpRight->Cut(1, 2);
            GameEngineImage* FlyLinkRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyLinkRight.bmp"));
            FlyLinkRight->Cut(1, 7);
			GameEngineImage* FlyDownRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlydownRight.bmp"));
			FlyDownRight->Cut(1, 2);

            GameEngineImage* FlyAwayRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FlyAwayRight.bmp"));
            FlyAwayRight->Cut(1, 32);
            GameEngineImage* SlideRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SlideRight.bmp"));
            SlideRight->Cut(1, 3);
            GameEngineImage* StandUpRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StandUpRight.bmp"));
            StandUpRight->Cut(1, 22);

			GameEngineImage* bazAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazAimRight.bmp"));
			bazAimRight->Cut(1, 32);
			GameEngineImage* bazOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOffRight.bmp"));
			bazOffRight->Cut(1, 7);
			GameEngineImage* bazOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("bazOnRight.bmp"));
			bazOnRight->Cut(1, 8);

            GameEngineImage* sheepOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOffRight.bmp"));
            sheepOffRight->Cut(1, 10);
            GameEngineImage* sheepOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("sheepOnRight.bmp"));
            sheepOnRight->Cut(1, 10);

            GameEngineImage* AirStrikeOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOffRight.bmp"));
            AirStrikeOffRight->Cut(1, 10);
            GameEngineImage* AirStrikeOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AirStrikeOnRight.bmp"));
            AirStrikeOnRight->Cut(1, 10);

            GameEngineImage* homingAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingAimRight.bmp"));
            homingAimRight->Cut(1, 32);
            GameEngineImage* homingOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOffRight.bmp"));
            homingOffRight->Cut(1, 7);
            GameEngineImage* homingOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("homingOnRight.bmp"));
            homingOnRight->Cut(1, 7);

            GameEngineImage* GrenadeAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeAimRight.bmp"));
            GrenadeAimRight->Cut(1, 32);
            GameEngineImage* GrenadeOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOffRight.bmp"));
            GrenadeOffRight->Cut(1,10);
            GameEngineImage* GrenadeOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GrenadeOnRight.bmp"));
            GrenadeOnRight->Cut(1, 10);

            GameEngineImage* TorchFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchFireRight.bmp"));
            TorchFireRight->Cut(1, 15);
            GameEngineImage* TorchOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOffRight.bmp"));
            TorchOffRight->Cut(1, 15);
            GameEngineImage* TorchOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TorchOnRight.bmp"));
            TorchOnRight->Cut(1, 15);


            GameEngineImage* DrillRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillRight.bmp"));
            DrillRight->Cut(1, 4);
            GameEngineImage* DrillOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOffRight.bmp"));
            DrillOffRight->Cut(1, 13);
            GameEngineImage* DrillOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("DrillOnRight.bmp"));
            DrillOnRight->Cut(1, 13);


            GameEngineImage* UziAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziAimRight.bmp"));
            UziAimRight->Cut(1, 32);
            GameEngineImage* UziFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziFireRight.bmp"));
            UziFireRight->Cut(1, 32);
            GameEngineImage* UziOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOffRight.bmp"));
            UziOffRight->Cut(1, 10);
            GameEngineImage* UziOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("UziOnRight.bmp"));
            UziOnRight->Cut(1, 10);        


            GameEngineImage* ClusterBombAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombAimRight.bmp"));
            ClusterBombAimRight->Cut(1, 32);
            //GameEngineImage* ClusterBombFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombFireRight.bmp"));
            //ClusterBombireRight->Cut(1, 32);
            GameEngineImage* ClusterBombOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOffRight.bmp"));
            ClusterBombOffRight->Cut(1, 10);
            GameEngineImage* ClusterBombOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClusterBombOnRight.bmp"));
            ClusterBombOnRight->Cut(1, 10);

            GameEngineImage* HandgunAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunAimRight.bmp"));
            HandgunAimRight->Cut(1, 32);
            GameEngineImage* HandgunFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunFireRight.bmp"));
            HandgunFireRight->Cut(1, 32);
            GameEngineImage* HandgunOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOffRight.bmp"));
            HandgunOffRight->Cut(1, 10);
            GameEngineImage* HandgunOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HandgunOnRight.bmp"));
            HandgunOnRight->Cut(1, 10);

            GameEngineImage* MinigunAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunAimRight.bmp"));
            MinigunAimRight->Cut(1, 32);
            GameEngineImage* MinigunFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunFireRight.bmp"));
            MinigunFireRight->Cut(1, 32);
            GameEngineImage* MinigunOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOffRight.bmp"));
            MinigunOffRight->Cut(1, 10);
            GameEngineImage* MinigunOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MinigunOnRight.bmp"));
            MinigunOnRight->Cut(1, 10);

            GameEngineImage* ShotgunAimRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunAimRight.bmp"));
            ShotgunAimRight->Cut(1, 32);
            GameEngineImage* ShotgunFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunFireRight.bmp"));
            ShotgunFireRight->Cut(1, 32);
            GameEngineImage* ShotgunOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOffRight.bmp"));
            ShotgunOffRight->Cut(1, 10);
            GameEngineImage* ShotgunOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShotgunOnRight.bmp"));
            ShotgunOnRight->Cut(1, 10);

            GameEngineImage* FirePunchChargingRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchChargingRight.bmp"));
            FirePunchChargingRight->Cut(1, 9);
            GameEngineImage* FirePunchFireRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchFireRight.bmp"));
            FirePunchFireRight->Cut(1, 3);
            GameEngineImage* FirePunchOffRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOffRight.bmp"));
            FirePunchOffRight->Cut(1, 26);
            GameEngineImage* FirePunchOnRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchOnRight.bmp"));
            FirePunchOnRight->Cut(1, 26);
            GameEngineImage* FirePunchAfterRight = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FirePunchAfterRight.bmp"));
            FirePunchAfterRight->Cut(1, 13);

		}
		Dir.MoveParent();
	}
	{
		Dir.Move("UIImage");
		{
			//플레이어 UI 이미지
			//본인 캐릭턴에 상단 화살표 이미지
			GameEngineImage* BlueArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowBlue.bmp"));
			BlueArrowImage->Cut(1, 30);
			GameEngineImage* GreenArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowGreen.bmp"));
			GreenArrowImage->Cut(1, 30);
			GameEngineImage* MintArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowMint.bmp"));
			MintArrowImage->Cut(1, 30);
			GameEngineImage* PinkArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowPink.bmp"));
			PinkArrowImage->Cut(1, 30);
			GameEngineImage* RedArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowRed.bmp"));
			RedArrowImage->Cut(1, 30);
			GameEngineImage* YellowArrowImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerSelectArrowYellow.bmp"));
			YellowArrowImage->Cut(1, 30);

			//캐릭터 체력 렌더 이미지
			GameEngineImage* BlueNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueNumberRender.bmp"));
			BlueNumberImage->Cut(10, 1);
			GameEngineImage* GreenNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GreenNumberRender.bmp"));
			GreenNumberImage->Cut(10, 1);
			GameEngineImage* MintNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MintNumberRender.bmp"));
			MintNumberImage->Cut(10, 1);
			GameEngineImage* RedNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RedNumberRender.bmp"));
			RedNumberImage->Cut(10, 1);
			GameEngineImage* PinkNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PinkNumberRender.bmp"));
			PinkNumberImage->Cut(10, 1);
			GameEngineImage* YellowNumberImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("YellowNumberRender.bmp"));
			YellowNumberImage->Cut(10, 1);

			//캐릭터 네임태그 이미지
			GameEngineImage* GreenNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GreenNameTag.bmp"));
			GameEngineImage* YellowNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("YellowNameTag.bmp"));
			GameEngineImage* PinkNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PinkNameTag.bmp"));
			GameEngineImage* MintNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MintNameTag.bmp"));
			GameEngineImage* RedNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RedNameTag.bmp"));
			GameEngineImage* BlueNametagImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueNameTag.bmp"));

			//캐릭터 체력 백그라운드 이미지
			GameEngineImage* PlayerHPBackgroundImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayerHPBackground.bmp"));
			Dir.MoveParent();
		}
		//UI
		{
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("weaponSheet.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("2020.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("WeaponIcon.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("bazookaUI.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("clusterUI.bmp"));
			}
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("grenadeUI.bmp"));
			}
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("shotgunUI.bmp"));
            }
			{
				GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("airstrkeUI.bmp"));
			}
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("torchUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("minigunUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("sheepUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("hmissileUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("handgunUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("uziUI.bmp"));
            }
            {
                GameEngineImage* WaeponInterface = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("X.bmp"));
            }

		}


        //WindBar UI
        {
        
            GameEngineImage* WindBarAnim = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windBar.bmp"));
            WindBarAnim->Cut(5, 4);
        
            GameEngineImage* WindBarGauge = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windGauge.bmp"));
            GameEngineImage* WindBarHider = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("windBarHider.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarB.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarG.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarP.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarR.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarS.bmp"));
        }
        {
            GameEngineImage* PlayerHPbar = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("BottomHPbarY.bmp"));
        }

        // Time UI
        {

            GameEngineImage* TimeNum = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerNum.bmp"));
            TimeNum->Cut(5, 2);
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowB.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowG.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowP.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowR.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowS.bmp"));
        }
        {
            GameEngineImage* TimeUI = GameEngineResources::GetInst().ImageLoad(InterFace.GetPlusFileName("TimerWindowY.bmp"));
        }
	}
	

}

void PlayLevel::KeyLoad()
{
	if (false == GameEngineInput::IsKey("ChangePlayer"))
	{
		GameEngineInput::CreateKey("ChangePlayer", 'n');
		GameEngineInput::CreateKey("DebugCollision", '8');
		GameEngineInput::CreateKey("WeaponUp", 'W');
		GameEngineInput::CreateKey("WeaponDown", 'S');
		GameEngineInput::CreateKey("Shoot", VK_SPACE);
	}
}

void PlayLevel::CreateLeaf(float _DeltaTime)
{

	AddWind.WindTime += _DeltaTime;
	if (AddWind.WindTime > 1.f)
	{
		for (int i = 0; i < 10; i++)
		{
           float X = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(-1000, 4000));
           float Y = static_cast<float>(GameEngineRandom::MainRandom.RandomInt(-1000, -500));

			float4 Pos = { X,Y };
			Leaf* pLeaf = CreateActor<Leaf>();
			pLeaf->SetPos(Pos);
		}
		AddWind.WindTime -= 1.f;

	}
}

void PlayLevel::PlayerChange(float _DeltaTime)
{
	//Player벡터 오류 검사
	if (-1 == iPlayerNumber)
	{
		MsgAssert("PlayerNumber가 -1 입니다.");
	}

    if (false == GlobalValue::gValue.GetPlayer()->GetIsMyTurn() ||GameEngineInput::IsDown("ChangePlayer"))
    {       
        //벡터 인덱스 증가
        ++iPlayerNumber;        

        //초과시 0
        if (vecAllPlayer.size() == iPlayerNumber)
        {
            iPlayerNumber = 0;
        }

        if (false == vecAllPlayer[iPlayerNumber]->IsUpdate())
        {
            PlayerChange(_DeltaTime);
            return;
        }
        //while (false == vecAllPlayer[iPlayerNumber]->IsUpdate())
        //{
        //    ++iPlayerNumber;
        //
        //    if (vecAllPlayer.size() == iPlayerNumber)
        //    {
        //        iPlayerNumber = 0;
        //    }
        //}

        //if (GlobalValue::gValue.GetPlayer() == vecAllPlayer[iPlayerNumber])
        //{
        //    MsgBox("게임 종료");
        //    return;
        //}

        //현재 플레이어의 턴 종료
        GlobalValue::gValue.GetPlayer()->SetIsMyTurn(false);

        //다음 플레이어가 현재 플레이어가됨
        GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);
        GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);

        CurPlayerPos = GlobalValue::gValue.GetPlayer()->GetPos();
        PrevCamPos = GetCameraPos();

        AllPlayerHpUI::AllHpUI->SetAllPlayerHP();
        bCamMove = true;
    }

	//플레이어가 변경되었다면
	if (bCamMove)
	{
		//1초동안 플레이어 카메라 위치 변경
		fLerpRatio += _DeltaTime * fLerpSpeed;
		SetCameraPos(LerpCamPos.LerpClamp(PrevCamPos, CurPlayerPos - ScreenSize.half(), fLerpRatio));

		if (fLerpRatio > 1.f)
		{
			bCamMove = false;
			fLerpRatio = 0.f;

			AddWind.WindPhase = GameEngineRandom::MainRandom.RandomInt(-10, 10);
			AddWind.WindResult = AddWind.WindPower * (AddWind.MaxWind * (static_cast<float>(AddWind.WindPhase) / 10.f));

			GlobalValue::gValue.SetWindSpeed(AddWind.WindResult);
			GlobalValue::gValue.SetWindPhase(AddWind.WindPhase);
		}
	}
}

void PlayLevel::MoveCamForMouse(float _DeltaTime)
{
	float4 CurCamPos = GetCameraPos() + ScreenSize.half();
	float4 CurMousePos = GetMousePosToCamera();
	float4 DistancePos = CurMousePos - CurCamPos;
	float4 MoveCam = float4::Zero;

	if (DistancePos.x > 500.f)
	{
		MoveCam += float4::Right;
	}
	if (DistancePos.x < -500.f)
	{
		MoveCam += float4::Left;
	}
	if (DistancePos.y < -350.f)
	{
		MoveCam += float4::Up;
	}
	if (DistancePos.y > 350.f)
	{
		MoveCam += float4::Down;
	}

	if (MoveCam.ix() == 0 && MoveCam.iy() == 0)
	{
		return;
	}

	MoveCam.Normalize();
	SetCameraMove(MoveCam * fCamMoveSpeed * _DeltaTime);
}





void PlayLevel::GameSetCheck()
{
    size_t iUpdatePlayer = vecAllPlayer.size();

    for (size_t i = 0; i < vecAllPlayer.size(); i++)
    {
        if (false==vecAllPlayer[i]->IsUpdate())
        {
            --iUpdatePlayer;
        }
    }

    if (1 == iUpdatePlayer)
    {
        int a = 0; // win
    }
    
    else if (0 == iUpdatePlayer)
    {
        int a = 0; // draw
    }
}

void PlayLevel::Loading()
{
	
	SoundLoad();
	ImageLoad();
	KeyLoad();
	
	
	/*{
		WeaponInterFace* Actor = CreateActor<WeaponInterFace>();
	}*/
 //   {
 //       Map* Actor = CreateActor<Map>();
 //   }


	//{
	//	MapModifier* ModifierActor = CreateActor<MapModifier>(WormsRenderOrder::Map);
	//}
	

    //{
    //    ScreenSize = GameEngineWindow::GetScreenSize();

    //    vecAllPlayer.reserve(6);
    //    for (size_t i = 0; i < 6; i++)
    //    {
    //        int iRandxPos = GameEngineRandom::MainRandom.RandomInt(0, 300);

    //        vecAllPlayer.push_back(CreateActor<Player>(WormsRenderOrder::Player));
    //        vecAllPlayer[i]->SetColImage(Map::MainMap->GetColMapName());

    //        float4 StartPos = float4{ 400,50 };
    //        StartPos.x *= i + 1;
    //        StartPos.x += iRandxPos;
    //        vecAllPlayer[i]->SetPos(StartPos);
    //    }
    //    GlobalValue::gValue.SetAllPlayer(vecAllPlayer);

    //    iPlayerNumber = 0;

    //    GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);

    //    GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);
    //    SetCameraPos(GlobalValue::gValue.GetPlayer()->GetPos() - ScreenSize.half());
    //}

   
    GlobalValue::gValue.SetPlayLevel(this);
    //CreateActor<WeaponFirePunch>();

}



void PlayLevel::Update(float _DeltaTime)
{
    GameSetCheck();
	CreateLeaf(_DeltaTime);     
    
    PlayerChange(_DeltaTime);
    
   
	//MoveCamForMouse(_DeltaTime);
	if (GameEngineInput::IsDown("DebugCollision"))
	{
		DebugRenderSwitch();
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
    {
        Map* Actor = CreateActor<Map>();
    }
    {
        MapModifier* ModifierActor = CreateActor<MapModifier>(WormsRenderOrder::Map);
    }
    {
        ScreenSize = GameEngineWindow::GetScreenSize();

        vecAllPlayer.reserve(LevelSet.iPlayerNum);
        vecTurnEnd.reserve(LevelSet.iPlayerNum);
        for (size_t i = 0; i < vecAllPlayer.capacity(); i++)
        {
            int iRandxPos = GameEngineRandom::MainRandom.RandomInt(0, 300);

            vecAllPlayer.push_back(CreateActor<Player>(WormsRenderOrder::Player));
            vecTurnEnd.push_back(false);
            vecAllPlayer[i]->SetColImage(Map::MainMap->GetColMapName());

            vecAllPlayer[i]->SetHP(LevelSet.iPlayerHp);

           
            float4 StartPos = float4{ 400,50 };
            StartPos.x *= i + 1;
            StartPos.x += iRandxPos;
            vecAllPlayer[i]->SetPos(StartPos);
            
            
        }
        GlobalValue::gValue.SetAllPlayer(vecAllPlayer);

        iPlayerNumber = 0;

        GlobalValue::gValue.SetPlayer(vecAllPlayer[iPlayerNumber]);

        GlobalValue::gValue.GetPlayer()->SetIsMyTurn(true);
        SetCameraPos(GlobalValue::gValue.GetPlayer()->GetPos() - ScreenSize.half());
    }
    {
        WeaponInterFace* Actor = CreateActor<WeaponInterFace>();
    }
    {
        AllPlayerHpUI* pAllPlayerHPUI = CreateActor<AllPlayerHpUI>();
        TurnTimeUI* pTurnTimeUI = CreateActor< TurnTimeUI>();
        WindUI* WindUIActor = CreateActor<WindUI>();

    }
    
    //CreateActor<WeaponAirStrike>();
    //CreateActor<HomingMissile>();
    //CreateActor<WeaponSheep>();
    //CreateActor<WeaponBazooka>();
    //CreateActor<WeaponTorch>();
    //CreateActor<WeaponDrill>();


	//CreateActor<WeaponHandgun>();
	//CreateActor<WeaponGrenade>();
	//CreateActor<WeaponUzi>();
	//CreateActor<WeaponMinigun>();
    //CreateActor<WeaponClusterBomb>();
    //CreateActor<WeaponShotgun>();
}